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
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* d; } ;
struct TYPE_5__ {scalar_t__ max; int /*<<< orphan*/  min; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_1__ dimen; TYPE_3__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHOGAIN_MINOUT ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int snd_echo_vumeters_info(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo)
{
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 96;
	uinfo->value.integer.min = ECHOGAIN_MINOUT;
	uinfo->value.integer.max = 0;
#ifdef ECHOCARD_HAS_VMIXER
	uinfo->dimen.d[0] = 3;	/* Out, In, Virt */
#else
	uinfo->dimen.d[0] = 2;	/* Out, In */
#endif
	uinfo->dimen.d[1] = 16;	/* 16 channels */
	uinfo->dimen.d[2] = 2;	/* 0=level, 1=peak */
	return 0;
}