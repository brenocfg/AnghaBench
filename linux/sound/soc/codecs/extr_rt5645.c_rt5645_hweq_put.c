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
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_5__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct rt5645_priv {TYPE_3__* eq_param; } ;
struct rt5645_eq_param_s_be16 {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct TYPE_6__ {scalar_t__ reg; void* val; } ;

/* Variables and functions */
 scalar_t__ RT5645_EQ_CTRL2 ; 
 int RT5645_HWEQ_NUM ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5645_validate_hweq (scalar_t__) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5645_hweq_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	struct rt5645_eq_param_s_be16 *eq_param =
		(struct rt5645_eq_param_s_be16 *)ucontrol->value.bytes.data;
	int i;

	for (i = 0; i < RT5645_HWEQ_NUM; i++) {
		rt5645->eq_param[i].reg = be16_to_cpu(eq_param[i].reg);
		rt5645->eq_param[i].val = be16_to_cpu(eq_param[i].val);
	}

	/* The final setting of the table should be RT5645_EQ_CTRL2 */
	for (i = RT5645_HWEQ_NUM - 1; i >= 0; i--) {
		if (rt5645->eq_param[i].reg == 0)
			continue;
		else if (rt5645->eq_param[i].reg != RT5645_EQ_CTRL2)
			return 0;
		else
			break;
	}

	for (i = 0; i < RT5645_HWEQ_NUM; i++) {
		if (!rt5645_validate_hweq(rt5645->eq_param[i].reg) &&
		    rt5645->eq_param[i].reg != 0)
			return 0;
		else if (rt5645->eq_param[i].reg == 0)
			break;
	}

	return 0;
}