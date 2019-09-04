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
struct wahc {scalar_t__ active_buf_in_urbs; int /*<<< orphan*/ * buf_in_urbs; int /*<<< orphan*/  xfer_id_count; scalar_t__ dto_in_use; int /*<<< orphan*/  xfer_error_work; int /*<<< orphan*/  xfer_enqueue_work; int /*<<< orphan*/  xfer_list_lock; int /*<<< orphan*/  xfer_errored_list; int /*<<< orphan*/  xfer_delayed_list; int /*<<< orphan*/  xfer_list; int /*<<< orphan*/  dti_edc; int /*<<< orphan*/  dti_state; int /*<<< orphan*/  notifs_queued; int /*<<< orphan*/  nep_edc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WA_DTI_TRANSFER_RESULT_PENDING ; 
 int WA_MAX_BUF_IN_URBS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  edc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_init_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wa_process_errored_transfers_run ; 
 int /*<<< orphan*/  wa_rpipe_init (struct wahc*) ; 
 int /*<<< orphan*/  wa_urb_enqueue_run ; 

__attribute__((used)) static inline void wa_init(struct wahc *wa)
{
	int index;

	edc_init(&wa->nep_edc);
	atomic_set(&wa->notifs_queued, 0);
	wa->dti_state = WA_DTI_TRANSFER_RESULT_PENDING;
	wa_rpipe_init(wa);
	edc_init(&wa->dti_edc);
	INIT_LIST_HEAD(&wa->xfer_list);
	INIT_LIST_HEAD(&wa->xfer_delayed_list);
	INIT_LIST_HEAD(&wa->xfer_errored_list);
	spin_lock_init(&wa->xfer_list_lock);
	INIT_WORK(&wa->xfer_enqueue_work, wa_urb_enqueue_run);
	INIT_WORK(&wa->xfer_error_work, wa_process_errored_transfers_run);
	wa->dto_in_use = 0;
	atomic_set(&wa->xfer_id_count, 1);
	/* init the buf in URBs */
	for (index = 0; index < WA_MAX_BUF_IN_URBS; ++index)
		usb_init_urb(&(wa->buf_in_urbs[index]));
	wa->active_buf_in_urbs = 0;
}