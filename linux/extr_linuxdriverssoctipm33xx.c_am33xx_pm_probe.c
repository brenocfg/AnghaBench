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
struct device {TYPE_1__* platform_data; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int (* init ) () ;int /*<<< orphan*/  (* get_sram_addrs ) () ;} ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  WFI_FLAG_FLUSH_CACHE ; 
 int /*<<< orphan*/  WFI_FLAG_SAVE_EMIF ; 
 int /*<<< orphan*/  WFI_FLAG_SELF_REFRESH ; 
 int /*<<< orphan*/  WFI_FLAG_WAKE_M3 ; 
 int am33xx_pm_alloc_sram () ; 
 int /*<<< orphan*/  am33xx_pm_free_sram () ; 
 int /*<<< orphan*/  am33xx_pm_set_ipc_ops () ; 
 int am33xx_push_sram_idle () ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  m3_ipc ; 
 int /*<<< orphan*/  of_machine_is_compatible (char*) ; 
 struct device* pm33xx_dev ; 
 TYPE_1__* pm_ops ; 
 int /*<<< orphan*/  pm_sram ; 
 int /*<<< orphan*/  stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  suspend_wfi_flags ; 
 int /*<<< orphan*/  wkup_m3_ipc_get () ; 
 int /*<<< orphan*/  wkup_m3_ipc_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_pm_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;

	if (!of_machine_is_compatible("ti,am33xx") &&
	    !of_machine_is_compatible("ti,am43"))
		return -ENODEV;

	pm_ops = dev->platform_data;
	if (!pm_ops) {
		dev_err(dev, "PM: Cannot get core PM ops!\n");
		return -ENODEV;
	}

	pm_sram = pm_ops->get_sram_addrs();
	if (!pm_sram) {
		dev_err(dev, "PM: Cannot get PM asm function addresses!!\n");
		return -ENODEV;
	}

	pm33xx_dev = dev;

	ret = am33xx_pm_alloc_sram();
	if (ret)
		return ret;

	ret = am33xx_push_sram_idle();
	if (ret)
		goto err_free_sram;

	m3_ipc = wkup_m3_ipc_get();
	if (!m3_ipc) {
		dev_dbg(dev, "PM: Cannot get wkup_m3_ipc handle\n");
		ret = -EPROBE_DEFER;
		goto err_free_sram;
	}

	am33xx_pm_set_ipc_ops();

#ifdef CONFIG_SUSPEND
	suspend_set_ops(&am33xx_pm_ops);
#endif /* CONFIG_SUSPEND */

	/*
	 * For a system suspend we must flush the caches, we want
	 * the DDR in self-refresh, we want to save the context
	 * of the EMIF, and we want the wkup_m3 to handle low-power
	 * transition.
	 */
	suspend_wfi_flags |= WFI_FLAG_FLUSH_CACHE;
	suspend_wfi_flags |= WFI_FLAG_SELF_REFRESH;
	suspend_wfi_flags |= WFI_FLAG_SAVE_EMIF;
	suspend_wfi_flags |= WFI_FLAG_WAKE_M3;

	ret = pm_ops->init();
	if (ret) {
		dev_err(dev, "Unable to call core pm init!\n");
		ret = -ENODEV;
		goto err_put_wkup_m3_ipc;
	}

	return 0;

err_put_wkup_m3_ipc:
	wkup_m3_ipc_put(m3_ipc);
err_free_sram:
	am33xx_pm_free_sram();
	pm33xx_dev = NULL;
	return ret;
}