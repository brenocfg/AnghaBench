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
struct async {int /*<<< orphan*/  mem_usage; TYPE_1__* urb; TYPE_2__* usbm; scalar_t__ cred; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {int /*<<< orphan*/  urb_use_count; } ;
struct TYPE_3__ {int num_sgs; struct async* setup_packet; struct async* transfer_buffer; struct async* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_usb_memory_use_count (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct async*) ; 
 int /*<<< orphan*/  put_cred (scalar_t__) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ sg_page (struct async*) ; 
 struct async* sg_virt (struct async*) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usbfs_decrease_memory_usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_async(struct async *as)
{
	int i;

	put_pid(as->pid);
	if (as->cred)
		put_cred(as->cred);
	for (i = 0; i < as->urb->num_sgs; i++) {
		if (sg_page(&as->urb->sg[i]))
			kfree(sg_virt(&as->urb->sg[i]));
	}

	kfree(as->urb->sg);
	if (as->usbm == NULL)
		kfree(as->urb->transfer_buffer);
	else
		dec_usb_memory_use_count(as->usbm, &as->usbm->urb_use_count);

	kfree(as->urb->setup_packet);
	usb_free_urb(as->urb);
	usbfs_decrease_memory_usage(as->mem_usage);
	kfree(as);
}