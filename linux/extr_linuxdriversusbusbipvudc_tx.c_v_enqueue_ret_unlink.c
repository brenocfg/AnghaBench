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
struct vudc {int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  ud; } ;
struct v_unlink {void* status; void* seqnum; } ;
struct tx_item {int /*<<< orphan*/  tx_entry; struct v_unlink* u; int /*<<< orphan*/  type; } ;
typedef  void* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TX_UNLINK ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_MALLOC ; 
 int /*<<< orphan*/  kfree (struct tx_item*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void v_enqueue_ret_unlink(struct vudc *udc, __u32 seqnum, __u32 status)
{
	struct tx_item *txi;
	struct v_unlink *unlink;

	txi = kzalloc(sizeof(*txi), GFP_ATOMIC);
	if (!txi) {
		usbip_event_add(&udc->ud, VDEV_EVENT_ERROR_MALLOC);
		return;
	}
	unlink = kzalloc(sizeof(*unlink), GFP_ATOMIC);
	if (!unlink) {
		kfree(txi);
		usbip_event_add(&udc->ud, VDEV_EVENT_ERROR_MALLOC);
		return;
	}

	unlink->seqnum = seqnum;
	unlink->status = status;
	txi->type = TX_UNLINK;
	txi->u = unlink;

	list_add_tail(&txi->tx_entry, &udc->tx_queue);
}