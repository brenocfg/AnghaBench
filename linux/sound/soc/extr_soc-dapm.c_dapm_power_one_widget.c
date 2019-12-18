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
struct snd_soc_dapm_widget {int id; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dapm_seq_insert (struct snd_soc_dapm_widget*,struct list_head*,int) ; 
 int dapm_widget_power_check (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  dapm_widget_set_power (struct snd_soc_dapm_widget*,int,struct list_head*,struct list_head*) ; 
#define  snd_soc_dapm_post 129 
#define  snd_soc_dapm_pre 128 

__attribute__((used)) static void dapm_power_one_widget(struct snd_soc_dapm_widget *w,
				  struct list_head *up_list,
				  struct list_head *down_list)
{
	int power;

	switch (w->id) {
	case snd_soc_dapm_pre:
		dapm_seq_insert(w, down_list, false);
		break;
	case snd_soc_dapm_post:
		dapm_seq_insert(w, up_list, true);
		break;

	default:
		power = dapm_widget_power_check(w);

		dapm_widget_set_power(w, power, up_list, down_list);
		break;
	}
}