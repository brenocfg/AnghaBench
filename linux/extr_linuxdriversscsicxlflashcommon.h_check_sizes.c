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

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON_NOT_POWER_OF_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXLFLASH_MAX_CMDS ; 
 int /*<<< orphan*/  CXLFLASH_NUM_FC_PORTS_PER_BANK ; 

__attribute__((used)) static inline void check_sizes(void)
{
	BUILD_BUG_ON_NOT_POWER_OF_2(CXLFLASH_NUM_FC_PORTS_PER_BANK);
	BUILD_BUG_ON_NOT_POWER_OF_2(CXLFLASH_MAX_CMDS);
}