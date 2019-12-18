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
struct axg_spdifin {TYPE_1__* conf; } ;
struct TYPE_2__ {int* mode_rates; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int axg_spdifin_mode_timer(struct axg_spdifin *priv,
					   int mode,
					   unsigned int rate)
{
	/*
	 * Number of period of the reference clock during a period of the
	 * input signal reference clock
	 */
	return rate / (128 * priv->conf->mode_rates[mode]);
}