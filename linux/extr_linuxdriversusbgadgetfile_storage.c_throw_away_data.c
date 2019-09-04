#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct fsg_dev {scalar_t__ usb_amount_left; struct fsg_buffhd* next_buffhd_to_fill; int /*<<< orphan*/  bulk_out; struct fsg_buffhd* next_buffhd_to_drain; } ;
struct fsg_buffhd {scalar_t__ state; scalar_t__ bulk_out_intended_length; struct fsg_buffhd* next; int /*<<< orphan*/  outreq_busy; TYPE_1__* outreq; } ;
struct TYPE_4__ {scalar_t__ buflen; } ;
struct TYPE_3__ {scalar_t__ actual; scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ BUF_STATE_EMPTY ; 
 scalar_t__ BUF_STATE_FULL ; 
 int EINTR ; 
 int /*<<< orphan*/  FSG_STATE_ABORT_BULK_OUT ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 TYPE_2__ mod_data ; 
 int /*<<< orphan*/  raise_exception (struct fsg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bulk_out_req_length (struct fsg_dev*,struct fsg_buffhd*,scalar_t__) ; 
 int sleep_thread (struct fsg_dev*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  start_transfer (struct fsg_dev*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int throw_away_data(struct fsg_dev *fsg)
{
	struct fsg_buffhd	*bh;
	u32			amount;
	int			rc;

	while ((bh = fsg->next_buffhd_to_drain)->state != BUF_STATE_EMPTY ||
			fsg->usb_amount_left > 0) {

		/* Throw away the data in a filled buffer */
		if (bh->state == BUF_STATE_FULL) {
			smp_rmb();
			bh->state = BUF_STATE_EMPTY;
			fsg->next_buffhd_to_drain = bh->next;

			/* A short packet or an error ends everything */
			if (bh->outreq->actual < bh->bulk_out_intended_length ||
					bh->outreq->status != 0) {
				raise_exception(fsg, FSG_STATE_ABORT_BULK_OUT);
				return -EINTR;
			}
			continue;
		}

		/* Try to submit another request if we need one */
		bh = fsg->next_buffhd_to_fill;
		if (bh->state == BUF_STATE_EMPTY && fsg->usb_amount_left > 0) {
			amount = min(fsg->usb_amount_left,
					(u32) mod_data.buflen);

			/* Except at the end of the transfer, amount will be
			 * equal to the buffer size, which is divisible by
			 * the bulk-out maxpacket size.
			 */
			set_bulk_out_req_length(fsg, bh, amount);
			start_transfer(fsg, fsg->bulk_out, bh->outreq,
					&bh->outreq_busy, &bh->state);
			fsg->next_buffhd_to_fill = bh->next;
			fsg->usb_amount_left -= amount;
			continue;
		}

		/* Otherwise wait for something to happen */
		rc = sleep_thread(fsg);
		if (rc)
			return rc;
	}
	return 0;
}