#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mpc8xxx_wdt_type {int prescaler; scalar_t__ hw_enabled; } ;
struct TYPE_8__ {int timeout; int max_hw_heartbeat_ms; int min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct mpc8xxx_wdt_ddata {int swtc; TYPE_1__ wdd; int /*<<< orphan*/  lock; TYPE_5__* base; } ;
struct TYPE_9__ {int /*<<< orphan*/  swcrr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_5__*) ; 
 int PTR_ERR (TYPE_5__*) ; 
 int SWCRR_SWEN ; 
 int WATCHDOG_TIMEOUT ; 
 TYPE_5__* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct mpc8xxx_wdt_ddata* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fsl_get_sys_freq () ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mpc8xxx_wdt_info ; 
 int /*<<< orphan*/  mpc8xxx_wdt_ops ; 
 int /*<<< orphan*/  mpc8xxx_wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 struct mpc8xxx_wdt_type* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mpc8xxx_wdt_ddata*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__ reset ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc8xxx_wdt_probe(struct platform_device *ofdev)
{
	int ret;
	struct resource *res;
	const struct mpc8xxx_wdt_type *wdt_type;
	struct mpc8xxx_wdt_ddata *ddata;
	u32 freq = fsl_get_sys_freq();
	bool enabled;

	wdt_type = of_device_get_match_data(&ofdev->dev);
	if (!wdt_type)
		return -EINVAL;

	if (!freq || freq == -1)
		return -EINVAL;

	ddata = devm_kzalloc(&ofdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	res = platform_get_resource(ofdev, IORESOURCE_MEM, 0);
	ddata->base = devm_ioremap_resource(&ofdev->dev, res);
	if (IS_ERR(ddata->base))
		return PTR_ERR(ddata->base);

	enabled = in_be32(&ddata->base->swcrr) & SWCRR_SWEN;
	if (!enabled && wdt_type->hw_enabled) {
		pr_info("could not be enabled in software\n");
		return -ENODEV;
	}

	spin_lock_init(&ddata->lock);

	ddata->wdd.info = &mpc8xxx_wdt_info,
	ddata->wdd.ops = &mpc8xxx_wdt_ops,

	ddata->wdd.timeout = WATCHDOG_TIMEOUT;
	watchdog_init_timeout(&ddata->wdd, timeout, &ofdev->dev);

	watchdog_set_nowayout(&ddata->wdd, nowayout);

	ddata->swtc = min(ddata->wdd.timeout * freq / wdt_type->prescaler,
			  0xffffU);

	/*
	 * If the watchdog was previously enabled or we're running on
	 * MPC8xxx, we should ping the wdt from the kernel until the
	 * userspace handles it.
	 */
	if (enabled)
		mpc8xxx_wdt_start(&ddata->wdd);

	ddata->wdd.max_hw_heartbeat_ms = (ddata->swtc * wdt_type->prescaler) /
					 (freq / 1000);
	ddata->wdd.min_timeout = ddata->wdd.max_hw_heartbeat_ms / 1000;
	if (ddata->wdd.timeout < ddata->wdd.min_timeout)
		ddata->wdd.timeout = ddata->wdd.min_timeout;

	ret = watchdog_register_device(&ddata->wdd);
	if (ret) {
		pr_err("cannot register watchdog device (err=%d)\n", ret);
		return ret;
	}

	pr_info("WDT driver for MPC8xxx initialized. mode:%s timeout=%d sec\n",
		reset ? "reset" : "interrupt", ddata->wdd.timeout);

	platform_set_drvdata(ofdev, ddata);
	return 0;
}