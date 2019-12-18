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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPDIFIN_CTRL4 ; 
 int /*<<< orphan*/  SPDIFIN_TIMER_PER_REG ; 
 int /*<<< orphan*/  SPDIFIN_TIMER_WIDTH ; 
 int /*<<< orphan*/  axg_spdifin_write_mode_param (struct regmap*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axg_spdifin_write_timer(struct regmap *map, int mode,
				    unsigned int val)
{
	axg_spdifin_write_mode_param(map, mode, val, SPDIFIN_TIMER_PER_REG,
				     SPDIFIN_CTRL4, SPDIFIN_TIMER_WIDTH);
}