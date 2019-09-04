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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBC_TOUPPER (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MACHINE_IS_VM ; 
 int /*<<< orphan*/  MAX_CMDLEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WDT_FUNC_CHANGE ; 
 unsigned int WDT_FUNC_CONCEAL ; 
 unsigned int WDT_FUNC_INIT ; 
 int __diag288_lpar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __diag288_vm (unsigned int,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ conceal_on ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 size_t strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_cmd ; 

__attribute__((used)) static int wdt_ping(struct watchdog_device *dev)
{
	char *ebc_cmd;
	size_t len;
	int ret;
	unsigned int func;

	ret = -ENODEV;

	if (MACHINE_IS_VM) {
		ebc_cmd = kmalloc(MAX_CMDLEN, GFP_KERNEL);
		if (!ebc_cmd)
			return -ENOMEM;
		len = strlcpy(ebc_cmd, wdt_cmd, MAX_CMDLEN);
		ASCEBC(ebc_cmd, MAX_CMDLEN);
		EBC_TOUPPER(ebc_cmd, MAX_CMDLEN);

		/*
		 * It seems to be ok to z/VM to use the init function to
		 * retrigger the watchdog. On LPAR WDT_FUNC_CHANGE must
		 * be used when the watchdog is running.
		 */
		func = conceal_on ? (WDT_FUNC_INIT | WDT_FUNC_CONCEAL)
			: WDT_FUNC_INIT;

		ret = __diag288_vm(func, dev->timeout, ebc_cmd, len);
		WARN_ON(ret != 0);
		kfree(ebc_cmd);
	} else {
		ret = __diag288_lpar(WDT_FUNC_CHANGE, dev->timeout, 0);
	}

	if (ret)
		pr_err("The watchdog timer cannot be started or reset\n");
	return ret;
}