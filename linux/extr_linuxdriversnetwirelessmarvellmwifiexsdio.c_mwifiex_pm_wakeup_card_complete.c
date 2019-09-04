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
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGURATION_REG ; 
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_pm_wakeup_card_complete(struct mwifiex_adapter *adapter)
{
	mwifiex_dbg(adapter, EVENT,
		    "cmd: wakeup device completed\n");

	return mwifiex_write_reg(adapter, CONFIGURATION_REG, 0);
}