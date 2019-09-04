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
struct fsg_dev {TYPE_1__* ep0; int /*<<< orphan*/  ep0req; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARNING (struct fsg_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int usb_ep_queue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep0_queue(struct fsg_dev *fsg)
{
	int	rc;

	rc = usb_ep_queue(fsg->ep0, fsg->ep0req, GFP_ATOMIC);
	if (rc != 0 && rc != -ESHUTDOWN) {

		/* We can't do much more than wait for a reset */
		WARNING(fsg, "error in submission: %s --> %d\n",
				fsg->ep0->name, rc);
	}
	return rc;
}