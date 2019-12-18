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

/* Variables and functions */
 int mtk_afe_add_sub_dai_control (struct snd_soc_component*) ; 

__attribute__((used)) static int mt6797_afe_component_probe(struct snd_soc_component *component)
{
	return mtk_afe_add_sub_dai_control(component);
}