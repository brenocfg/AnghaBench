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
struct list_head {int dummy; } ;
struct brcmf_usbreq {int /*<<< orphan*/  list; } ;
struct brcmf_usbdev_info {int /*<<< orphan*/  qlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void brcmf_usb_enq(struct brcmf_usbdev_info *devinfo,
			  struct list_head *q, struct brcmf_usbreq *req,
			  int *counter)
{
	unsigned long flags;
	spin_lock_irqsave(&devinfo->qlock, flags);
	list_add_tail(&req->list, q);
	if (counter)
		(*counter)++;
	spin_unlock_irqrestore(&devinfo->qlock, flags);
}