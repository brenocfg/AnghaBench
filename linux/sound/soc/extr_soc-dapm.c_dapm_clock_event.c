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
struct snd_soc_dapm_widget {int /*<<< orphan*/  clk; int /*<<< orphan*/  dapm; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_dapm_async_complete (int /*<<< orphan*/ ) ; 

int dapm_clock_event(struct snd_soc_dapm_widget *w,
		   struct snd_kcontrol *kcontrol, int event)
{
	if (!w->clk)
		return -EIO;

	soc_dapm_async_complete(w->dapm);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		return clk_prepare_enable(w->clk);
	} else {
		clk_disable_unprepare(w->clk);
		return 0;
	}

	return 0;
}