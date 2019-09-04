#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_endpoint_descriptor {int dummy; } ;
struct urb {unsigned int transfer_buffer_length; unsigned int actual_length; unsigned int number_of_packets; int /*<<< orphan*/  error_count; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  interval; int /*<<< orphan*/  transfer_flags; TYPE_3__* dev; TYPE_1__* ep; } ;
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct mon_reader_bin {int b_size; int /*<<< orphan*/  b_wait; int /*<<< orphan*/  b_lock; int /*<<< orphan*/  cnt_lost; scalar_t__ mmap_active; } ;
struct mon_bin_isodesc {int dummy; } ;
struct TYPE_9__ {unsigned int numdesc; int /*<<< orphan*/  error_count; } ;
struct TYPE_10__ {int /*<<< orphan*/  setup; TYPE_4__ iso; } ;
struct mon_bin_hdr {char type; unsigned char epnum; unsigned long id; int ts_usec; int status; unsigned int len_urb; unsigned int len_cap; char flag_setup; unsigned int ndesc; char flag_data; TYPE_5__ s; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  interval; int /*<<< orphan*/  xfer_flags; int /*<<< orphan*/  ts_sec; int /*<<< orphan*/  busnum; int /*<<< orphan*/  devnum; int /*<<< orphan*/  xfer_type; } ;
struct TYPE_8__ {TYPE_2__* bus; int /*<<< orphan*/  devnum; } ;
struct TYPE_7__ {int /*<<< orphan*/  busnum; } ;
struct TYPE_6__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 unsigned int ISODESC_MAX ; 
 struct mon_bin_hdr* MON_OFF2HDR (struct mon_reader_bin*,unsigned int) ; 
 int NSEC_PER_USEC ; 
 int PKT_ALIGN ; 
 int PKT_SIZE ; 
 unsigned char USB_DIR_IN ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  memset (struct mon_bin_hdr*,int /*<<< orphan*/ ,int) ; 
 unsigned int mon_bin_collate_isodesc (struct mon_reader_bin*,struct urb*,unsigned int) ; 
 unsigned int mon_bin_get_data (struct mon_reader_bin*,unsigned int,struct urb*,unsigned int,char*) ; 
 int /*<<< orphan*/  mon_bin_get_isodesc (struct mon_reader_bin*,unsigned int,struct urb*,char,unsigned int) ; 
 char mon_bin_get_setup (int /*<<< orphan*/ ,struct urb*,char) ; 
 unsigned int mon_buff_area_alloc (struct mon_reader_bin*,int) ; 
 unsigned int mon_buff_area_alloc_contiguous (struct mon_reader_bin*,int) ; 
 int /*<<< orphan*/  mon_buff_area_shrink (struct mon_reader_bin*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char usb_endpoint_num (struct usb_endpoint_descriptor const*) ; 
 size_t usb_endpoint_type (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_control (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_int (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_isoc (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfer_to_pipe ; 

__attribute__((used)) static void mon_bin_event(struct mon_reader_bin *rp, struct urb *urb,
    char ev_type, int status)
{
	const struct usb_endpoint_descriptor *epd = &urb->ep->desc;
	struct timespec64 ts;
	unsigned long flags;
	unsigned int urb_length;
	unsigned int offset;
	unsigned int length;
	unsigned int delta;
	unsigned int ndesc, lendesc;
	unsigned char dir;
	struct mon_bin_hdr *ep;
	char data_tag = 0;

	ktime_get_real_ts64(&ts);

	spin_lock_irqsave(&rp->b_lock, flags);

	/*
	 * Find the maximum allowable length, then allocate space.
	 */
	urb_length = (ev_type == 'S') ?
	    urb->transfer_buffer_length : urb->actual_length;
	length = urb_length;

	if (usb_endpoint_xfer_isoc(epd)) {
		if (urb->number_of_packets < 0) {
			ndesc = 0;
		} else if (urb->number_of_packets >= ISODESC_MAX) {
			ndesc = ISODESC_MAX;
		} else {
			ndesc = urb->number_of_packets;
		}
		if (ev_type == 'C' && usb_urb_dir_in(urb))
			length = mon_bin_collate_isodesc(rp, urb, ndesc);
	} else {
		ndesc = 0;
	}
	lendesc = ndesc*sizeof(struct mon_bin_isodesc);

	/* not an issue unless there's a subtle bug in a HCD somewhere */
	if (length >= urb->transfer_buffer_length)
		length = urb->transfer_buffer_length;

	if (length >= rp->b_size/5)
		length = rp->b_size/5;

	if (usb_urb_dir_in(urb)) {
		if (ev_type == 'S') {
			length = 0;
			data_tag = '<';
		}
		/* Cannot rely on endpoint number in case of control ep.0 */
		dir = USB_DIR_IN;
	} else {
		if (ev_type == 'C') {
			length = 0;
			data_tag = '>';
		}
		dir = 0;
	}

	if (rp->mmap_active) {
		offset = mon_buff_area_alloc_contiguous(rp,
						 length + PKT_SIZE + lendesc);
	} else {
		offset = mon_buff_area_alloc(rp, length + PKT_SIZE + lendesc);
	}
	if (offset == ~0) {
		rp->cnt_lost++;
		spin_unlock_irqrestore(&rp->b_lock, flags);
		return;
	}

	ep = MON_OFF2HDR(rp, offset);
	if ((offset += PKT_SIZE) >= rp->b_size) offset = 0;

	/*
	 * Fill the allocated area.
	 */
	memset(ep, 0, PKT_SIZE);
	ep->type = ev_type;
	ep->xfer_type = xfer_to_pipe[usb_endpoint_type(epd)];
	ep->epnum = dir | usb_endpoint_num(epd);
	ep->devnum = urb->dev->devnum;
	ep->busnum = urb->dev->bus->busnum;
	ep->id = (unsigned long) urb;
	ep->ts_sec = ts.tv_sec;
	ep->ts_usec = ts.tv_nsec / NSEC_PER_USEC;
	ep->status = status;
	ep->len_urb = urb_length;
	ep->len_cap = length + lendesc;
	ep->xfer_flags = urb->transfer_flags;

	if (usb_endpoint_xfer_int(epd)) {
		ep->interval = urb->interval;
	} else if (usb_endpoint_xfer_isoc(epd)) {
		ep->interval = urb->interval;
		ep->start_frame = urb->start_frame;
		ep->s.iso.error_count = urb->error_count;
		ep->s.iso.numdesc = urb->number_of_packets;
	}

	if (usb_endpoint_xfer_control(epd) && ev_type == 'S') {
		ep->flag_setup = mon_bin_get_setup(ep->s.setup, urb, ev_type);
	} else {
		ep->flag_setup = '-';
	}

	if (ndesc != 0) {
		ep->ndesc = ndesc;
		mon_bin_get_isodesc(rp, offset, urb, ev_type, ndesc);
		if ((offset += lendesc) >= rp->b_size)
			offset -= rp->b_size;
	}

	if (length != 0) {
		length = mon_bin_get_data(rp, offset, urb, length,
				&ep->flag_data);
		if (length > 0) {
			delta = (ep->len_cap + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
			ep->len_cap -= length;
			delta -= (ep->len_cap + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
			mon_buff_area_shrink(rp, delta);
		}
	} else {
		ep->flag_data = data_tag;
	}

	spin_unlock_irqrestore(&rp->b_lock, flags);

	wake_up(&rp->b_wait);
}