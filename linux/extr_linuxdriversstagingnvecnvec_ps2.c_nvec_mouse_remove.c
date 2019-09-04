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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct nvec_chip {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ser_dev; int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_MOUSE ; 
 struct nvec_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvec_unregister_notifier (struct nvec_chip*,int /*<<< orphan*/ *) ; 
 TYPE_2__ ps2_dev ; 
 int /*<<< orphan*/  ps2_sendcommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2_stopstreaming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvec_mouse_remove(struct platform_device *pdev)
{
	struct nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);

	ps2_sendcommand(ps2_dev.ser_dev, DISABLE_MOUSE);
	ps2_stopstreaming(ps2_dev.ser_dev);
	nvec_unregister_notifier(nvec, &ps2_dev.notifier);
	serio_unregister_port(ps2_dev.ser_dev);

	return 0;
}