#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ffs_data {int /*<<< orphan*/  flags; TYPE_1__* gadget; int /*<<< orphan*/ * ep0req; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  FFS_FL_BOUND ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffs_data_put (struct ffs_data*) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void functionfs_unbind(struct ffs_data *ffs)
{
	ENTER();

	if (!WARN_ON(!ffs->gadget)) {
		usb_ep_free_request(ffs->gadget->ep0, ffs->ep0req);
		ffs->ep0req = NULL;
		ffs->gadget = NULL;
		clear_bit(FFS_FL_BOUND, &ffs->flags);
		ffs_data_put(ffs);
	}
}