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
struct rfkill {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rfkill*) ; 
 struct rfkill* rfkill_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_ops ; 
 int rfkill_register (struct rfkill*) ; 

__attribute__((used)) static int xo1_rfkill_probe(struct platform_device *pdev)
{
	struct rfkill *rfk;
	int r;

	rfk = rfkill_alloc(pdev->name, &pdev->dev, RFKILL_TYPE_WLAN,
			   &rfkill_ops, NULL);
	if (!rfk)
		return -ENOMEM;

	r = rfkill_register(rfk);
	if (r) {
		rfkill_destroy(rfk);
		return r;
	}

	platform_set_drvdata(pdev, rfk);
	return 0;
}