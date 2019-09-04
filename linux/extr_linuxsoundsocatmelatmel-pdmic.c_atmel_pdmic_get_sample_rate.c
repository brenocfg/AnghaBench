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
typedef  scalar_t__ u32 ;
struct atmel_pdmic {int /*<<< orphan*/  gclk; int /*<<< orphan*/  pclk; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ mic_min_freq; scalar_t__ mic_max_freq; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (scalar_t__,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_pdmic_get_sample_rate(struct atmel_pdmic *dd,
	unsigned int *rate_min, unsigned int *rate_max)
{
	u32 mic_min_freq = dd->pdata->mic_min_freq;
	u32 mic_max_freq = dd->pdata->mic_max_freq;
	u32 clk_max_rate = (u32)(clk_get_rate(dd->pclk) >> 1);
	u32 clk_min_rate = (u32)(clk_get_rate(dd->gclk) >> 8);

	if (mic_max_freq > clk_max_rate)
		mic_max_freq = clk_max_rate;

	if (mic_min_freq < clk_min_rate)
		mic_min_freq = clk_min_rate;

	*rate_min = DIV_ROUND_CLOSEST(mic_min_freq, 128);
	*rate_max = mic_max_freq >> 6;
}