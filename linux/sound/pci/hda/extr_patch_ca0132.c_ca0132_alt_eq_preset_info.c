#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {unsigned int items; unsigned int item; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_1__ value; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 TYPE_3__* ca0132_alt_eq_presets ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca0132_alt_eq_preset_info(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo)
{
	unsigned int items = ARRAY_SIZE(ca0132_alt_eq_presets);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = items;
	if (uinfo->value.enumerated.item >= items)
		uinfo->value.enumerated.item = items - 1;
	strcpy(uinfo->value.enumerated.name,
		ca0132_alt_eq_presets[uinfo->value.enumerated.item].name);
	return 0;
}