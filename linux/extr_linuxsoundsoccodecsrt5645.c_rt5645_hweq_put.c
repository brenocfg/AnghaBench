#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct rt5645_priv {int /*<<< orphan*/  eq_param; } ;
struct rt5645_eq_param_s {scalar_t__ reg; scalar_t__ val; } ;

/* Variables and functions */
 scalar_t__ RT5645_EQ_CTRL2 ; 
 int RT5645_HWEQ_NUM ; 
 void* be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct rt5645_eq_param_s*,int) ; 
 int /*<<< orphan*/  rt5645_validate_hweq (scalar_t__) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5645_hweq_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	struct rt5645_eq_param_s *eq_param =
		(struct rt5645_eq_param_s *)ucontrol->value.bytes.data;
	int i;

	for (i = 0; i < RT5645_HWEQ_NUM; i++) {
		eq_param[i].reg = be16_to_cpu(eq_param[i].reg);
		eq_param[i].val = be16_to_cpu(eq_param[i].val);
	}

	/* The final setting of the table should be RT5645_EQ_CTRL2 */
	for (i = RT5645_HWEQ_NUM - 1; i >= 0; i--) {
		if (eq_param[i].reg == 0)
			continue;
		else if (eq_param[i].reg != RT5645_EQ_CTRL2)
			return 0;
		else
			break;
	}

	for (i = 0; i < RT5645_HWEQ_NUM; i++) {
		if (!rt5645_validate_hweq(eq_param[i].reg) &&
			eq_param[i].reg != 0)
			return 0;
		else if (eq_param[i].reg == 0)
			break;
	}

	memcpy(rt5645->eq_param, eq_param,
		RT5645_HWEQ_NUM * sizeof(struct rt5645_eq_param_s));

	return 0;
}