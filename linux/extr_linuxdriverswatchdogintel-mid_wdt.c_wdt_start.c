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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int timeout; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ipc_wd_start ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  MID_WDT_PRETIMEOUT ; 
 int /*<<< orphan*/  SCU_WATCHDOG_START ; 
 int /*<<< orphan*/  dev_crit (struct device*,char*,int) ; 
 struct device* watchdog_get_drvdata (struct watchdog_device*) ; 
 int wdt_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wdt_start(struct watchdog_device *wd)
{
	struct device *dev = watchdog_get_drvdata(wd);
	int ret, in_size;
	int timeout = wd->timeout;
	struct ipc_wd_start {
		u32 pretimeout;
		u32 timeout;
	} ipc_wd_start = { timeout - MID_WDT_PRETIMEOUT, timeout };

	/*
	 * SCU expects the input size for watchdog IPC to
	 * be based on 4 bytes
	 */
	in_size = DIV_ROUND_UP(sizeof(ipc_wd_start), 4);

	ret = wdt_command(SCU_WATCHDOG_START, (u32 *)&ipc_wd_start, in_size);
	if (ret)
		dev_crit(dev, "error starting watchdog: %d\n", ret);

	return ret;
}