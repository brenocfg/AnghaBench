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
struct TYPE_4__ {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 char CNFG_WAKE_KEY_REPORTING ; 
 char DISABLE_KBD ; 
 char NVEC_KBD ; 
 struct nvec_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_2__ keys_dev ; 
 int /*<<< orphan*/  nvec_unregister_notifier (struct nvec_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvec_write_async (struct nvec_chip*,char*,int) ; 

__attribute__((used)) static int nvec_kbd_remove(struct platform_device *pdev)
{
	struct nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	char disable_kbd[] = { NVEC_KBD, DISABLE_KBD },
	     uncnfg_wake_key_reporting[] = { NVEC_KBD, CNFG_WAKE_KEY_REPORTING,
						false };
	nvec_write_async(nvec, uncnfg_wake_key_reporting, 3);
	nvec_write_async(nvec, disable_kbd, 2);
	nvec_unregister_notifier(nvec, &keys_dev.notifier);

	return 0;
}