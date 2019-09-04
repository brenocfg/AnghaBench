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
struct platform_device {int dummy; } ;
struct dummy {int /*<<< orphan*/ * ss_hcd; int /*<<< orphan*/ * hs_hcd; } ;
struct TYPE_2__ {struct dummy* dum; } ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_hcd_to_hcd (int /*<<< orphan*/ *) ; 
 TYPE_1__* hcd_to_dummy_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_put_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_hcd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dummy_hcd_remove(struct platform_device *pdev)
{
	struct dummy		*dum;

	dum = hcd_to_dummy_hcd(platform_get_drvdata(pdev))->dum;

	if (dum->ss_hcd) {
		usb_remove_hcd(dummy_hcd_to_hcd(dum->ss_hcd));
		usb_put_hcd(dummy_hcd_to_hcd(dum->ss_hcd));
	}

	usb_remove_hcd(dummy_hcd_to_hcd(dum->hs_hcd));
	usb_put_hcd(dummy_hcd_to_hcd(dum->hs_hcd));

	dum->hs_hcd = NULL;
	dum->ss_hcd = NULL;

	return 0;
}