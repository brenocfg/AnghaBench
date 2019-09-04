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
struct hdspm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_RD_PLL_FREQ ; 
 unsigned int hdspm_calc_dds_value (struct hdspm*,unsigned int) ; 
 unsigned int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hdspm_get_pll_freq(struct hdspm *hdspm)
{
	unsigned int period, rate;

	period = hdspm_read(hdspm, HDSPM_RD_PLL_FREQ);
	rate = hdspm_calc_dds_value(hdspm, period);

	return rate;
}