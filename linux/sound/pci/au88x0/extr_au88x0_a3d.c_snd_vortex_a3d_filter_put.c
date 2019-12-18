#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {TYPE_3__* private_data; } ;
struct TYPE_6__ {int* value; } ;
struct TYPE_7__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_8__ {int /*<<< orphan*/ * filter; } ;
typedef  TYPE_3__ a3dsrc_t ;

/* Variables and functions */
 int /*<<< orphan*/  a3dsrc_SetAtmosCurrent (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a3dsrc_SetAtmosTarget (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_a3d_translate_filter (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
snd_vortex_a3d_filter_put(struct snd_kcontrol *kcontrol,
			  struct snd_ctl_elem_value *ucontrol)
{
	a3dsrc_t *a = kcontrol->private_data;
	int i;
	int params[6];
	for (i = 0; i < 6; i++)
		params[i] = ucontrol->value.integer.value[i];
	/* Translate generic filter params to a3d filter params. */
	vortex_a3d_translate_filter(a->filter, params);
	/* Atmospheric absorption and filtering. */
	a3dsrc_SetAtmosTarget(a, a->filter[0],
			      a->filter[1], a->filter[2],
			      a->filter[3], a->filter[4]);
	a3dsrc_SetAtmosCurrent(a, a->filter[0],
			       a->filter[1], a->filter[2],
			       a->filter[3], a->filter[4]);
	return 1;
}