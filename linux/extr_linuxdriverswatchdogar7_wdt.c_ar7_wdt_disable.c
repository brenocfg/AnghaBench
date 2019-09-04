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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  disable; int /*<<< orphan*/  disable_lock; } ;

/* Variables and functions */
 int READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ar7_wdt ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ar7_wdt_disable(u32 value)
{
	WRITE_REG(ar7_wdt->disable_lock, 0x7777);
	if ((READ_REG(ar7_wdt->disable_lock) & 3) == 1) {
		WRITE_REG(ar7_wdt->disable_lock, 0xcccc);
		if ((READ_REG(ar7_wdt->disable_lock) & 3) == 2) {
			WRITE_REG(ar7_wdt->disable_lock, 0xdddd);
			if ((READ_REG(ar7_wdt->disable_lock) & 3) == 3) {
				WRITE_REG(ar7_wdt->disable, value);
				return;
			}
		}
	}
	pr_err("failed to unlock WDT disable reg\n");
}