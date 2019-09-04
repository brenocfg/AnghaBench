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
struct phy_devm {int /*<<< orphan*/  phy; scalar_t__ nb; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unregister_notifier (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void devm_usb_phy_release2(struct device *dev, void *_res)
{
	struct phy_devm *res = _res;

	if (res->nb)
		usb_unregister_notifier(res->phy, res->nb);
	usb_put_phy(res->phy);
}