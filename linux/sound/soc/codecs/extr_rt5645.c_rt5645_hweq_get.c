#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_2__ bytes; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct rt5645_priv {TYPE_1__* eq_param; } ;
struct rt5645_eq_param_s_be16 {void* val; void* reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int RT5645_HWEQ_NUM ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5645_hweq_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	struct rt5645_eq_param_s_be16 *eq_param =
		(struct rt5645_eq_param_s_be16 *)ucontrol->value.bytes.data;
	int i;

	for (i = 0; i < RT5645_HWEQ_NUM; i++) {
		eq_param[i].reg = cpu_to_be16(rt5645->eq_param[i].reg);
		eq_param[i].val = cpu_to_be16(rt5645->eq_param[i].val);
	}

	return 0;
}