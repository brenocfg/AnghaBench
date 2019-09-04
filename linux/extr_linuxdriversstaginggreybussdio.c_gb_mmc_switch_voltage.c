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
struct mmc_ios {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int gb_mmc_switch_voltage(struct mmc_host *mmc, struct mmc_ios *ios)
{
	return 0;
}