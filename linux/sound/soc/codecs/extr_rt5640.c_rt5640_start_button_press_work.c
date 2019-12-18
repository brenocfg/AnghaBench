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
struct rt5640_priv {int pressed; int press_reported; int /*<<< orphan*/  bp_work; scalar_t__ release_count; scalar_t__ press_count; scalar_t__ poll_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_POLL_TIME ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5640_clear_micbias1_ovcd (struct snd_soc_component*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void rt5640_start_button_press_work(struct snd_soc_component *component)
{
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	rt5640->poll_count = 0;
	rt5640->press_count = 0;
	rt5640->release_count = 0;
	rt5640->pressed = false;
	rt5640->press_reported = false;
	rt5640_clear_micbias1_ovcd(component);
	schedule_delayed_work(&rt5640->bp_work, msecs_to_jiffies(BP_POLL_TIME));
}