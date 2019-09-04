#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct urb {scalar_t__ interval; } ;
struct fotg210_iso_stream {scalar_t__ interval; } ;
struct fotg210_hcd {int periodic_size; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_PORT_STAT_HIGH_SPEED ; 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,...) ; 
 scalar_t__ fotg210_port_speed (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fotg210_to_hcd (struct fotg210_hcd*) ; 
 struct fotg210_iso_stream* iso_stream_find (struct fotg210_hcd*,struct urb*) ; 
 int iso_stream_schedule (struct fotg210_hcd*,struct urb*,struct fotg210_iso_stream*) ; 
 int /*<<< orphan*/  itd_link_urb (struct fotg210_hcd*,struct urb*,int,struct fotg210_iso_stream*) ; 
 int itd_urb_transaction (struct fotg210_iso_stream*,struct fotg210_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int usb_hcd_link_urb_to_ep (int /*<<< orphan*/ ,struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 

__attribute__((used)) static int itd_submit(struct fotg210_hcd *fotg210, struct urb *urb,
		gfp_t mem_flags)
{
	int status = -EINVAL;
	unsigned long flags;
	struct fotg210_iso_stream *stream;

	/* Get iso_stream head */
	stream = iso_stream_find(fotg210, urb);
	if (unlikely(stream == NULL)) {
		fotg210_dbg(fotg210, "can't get iso stream\n");
		return -ENOMEM;
	}
	if (unlikely(urb->interval != stream->interval &&
			fotg210_port_speed(fotg210, 0) ==
			USB_PORT_STAT_HIGH_SPEED)) {
		fotg210_dbg(fotg210, "can't change iso interval %d --> %d\n",
				stream->interval, urb->interval);
		goto done;
	}

#ifdef FOTG210_URB_TRACE
	fotg210_dbg(fotg210,
			"%s %s urb %p ep%d%s len %d, %d pkts %d uframes[%p]\n",
			__func__, urb->dev->devpath, urb,
			usb_pipeendpoint(urb->pipe),
			usb_pipein(urb->pipe) ? "in" : "out",
			urb->transfer_buffer_length,
			urb->number_of_packets, urb->interval,
			stream);
#endif

	/* allocate ITDs w/o locking anything */
	status = itd_urb_transaction(stream, fotg210, urb, mem_flags);
	if (unlikely(status < 0)) {
		fotg210_dbg(fotg210, "can't init itds\n");
		goto done;
	}

	/* schedule ... need to lock */
	spin_lock_irqsave(&fotg210->lock, flags);
	if (unlikely(!HCD_HW_ACCESSIBLE(fotg210_to_hcd(fotg210)))) {
		status = -ESHUTDOWN;
		goto done_not_linked;
	}
	status = usb_hcd_link_urb_to_ep(fotg210_to_hcd(fotg210), urb);
	if (unlikely(status))
		goto done_not_linked;
	status = iso_stream_schedule(fotg210, urb, stream);
	if (likely(status == 0))
		itd_link_urb(fotg210, urb, fotg210->periodic_size << 3, stream);
	else
		usb_hcd_unlink_urb_from_ep(fotg210_to_hcd(fotg210), urb);
done_not_linked:
	spin_unlock_irqrestore(&fotg210->lock, flags);
done:
	return status;
}