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
struct TYPE_2__ {int /*<<< orphan*/  default_ticks; int /*<<< orphan*/  timer; scalar_t__ queue; int /*<<< orphan*/  stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU5WDT_EXTENT ; 
 scalar_t__ CPU5WDT_STATUS_REG ; 
 int EBUSY ; 
 int /*<<< orphan*/  PFX ; 
 TYPE_1__ cpu5wdt_device ; 
 int /*<<< orphan*/  cpu5wdt_misc ; 
 int /*<<< orphan*/  cpu5wdt_trigger ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 scalar_t__ port ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int cpu5wdt_init(void)
{
	unsigned int val;
	int err;

	if (verbose)
		pr_debug("port=0x%x, verbose=%i\n", port, verbose);

	init_completion(&cpu5wdt_device.stop);
	cpu5wdt_device.queue = 0;
	timer_setup(&cpu5wdt_device.timer, cpu5wdt_trigger, 0);
	cpu5wdt_device.default_ticks = ticks;

	if (!request_region(port, CPU5WDT_EXTENT, PFX)) {
		pr_err("request_region failed\n");
		err = -EBUSY;
		goto no_port;
	}

	/* watchdog reboot? */
	val = inb(port + CPU5WDT_STATUS_REG);
	val = (val >> 2) & 1;
	if (!val)
		pr_info("sorry, was my fault\n");

	err = misc_register(&cpu5wdt_misc);
	if (err < 0) {
		pr_err("misc_register failed\n");
		goto no_misc;
	}


	pr_info("init success\n");
	return 0;

no_misc:
	release_region(port, CPU5WDT_EXTENT);
no_port:
	return err;
}