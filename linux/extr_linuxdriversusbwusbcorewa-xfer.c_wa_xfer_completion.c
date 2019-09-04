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
struct wa_xfer {TYPE_1__* ep; scalar_t__ wusb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  hcpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpipe_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_xfer_giveback (struct wa_xfer*) ; 
 int /*<<< orphan*/  wusb_dev_put (scalar_t__) ; 

__attribute__((used)) static void wa_xfer_completion(struct wa_xfer *xfer)
{
	if (xfer->wusb_dev)
		wusb_dev_put(xfer->wusb_dev);
	rpipe_put(xfer->ep->hcpriv);
	wa_xfer_giveback(xfer);
}