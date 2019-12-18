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
struct snd_soc_dapm_widget {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_DIR_OUT ; 
 int is_connected_ep (struct snd_soc_dapm_widget*,struct list_head*,int /*<<< orphan*/ ,int (*) (struct snd_soc_dapm_widget*,struct list_head*,int (*) (struct snd_soc_dapm_widget*,int)),int (*) (struct snd_soc_dapm_widget*,int)) ; 

__attribute__((used)) static int is_connected_output_ep(struct snd_soc_dapm_widget *widget,
	struct list_head *list,
	bool (*custom_stop_condition)(struct snd_soc_dapm_widget *i,
				      enum snd_soc_dapm_direction))
{
	return is_connected_ep(widget, list, SND_SOC_DAPM_DIR_OUT,
			is_connected_output_ep, custom_stop_condition);
}