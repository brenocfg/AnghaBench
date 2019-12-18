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
struct snd_soc_component {int dummy; } ;
struct rt5651_priv {int pressed; int press_reported; int /*<<< orphan*/  bp_work; scalar_t__ release_count; scalar_t__ press_count; scalar_t__ poll_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_POLL_TIME ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5651_clear_micbias1_ovcd (struct snd_soc_component*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rt5651_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void rt5651_start_button_press_work(struct snd_soc_component *component)
{
	struct rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	rt5651->poll_count = 0;
	rt5651->press_count = 0;
	rt5651->release_count = 0;
	rt5651->pressed = false;
	rt5651->press_reported = false;
	rt5651_clear_micbias1_ovcd(component);
	schedule_delayed_work(&rt5651->bp_work, msecs_to_jiffies(BP_POLL_TIME));
}