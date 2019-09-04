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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_MAX_ELD_BYTES ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BYTES ; 

__attribute__((used)) static int had_ctl_eld_info(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_info *uinfo)
{
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = HDMI_MAX_ELD_BYTES;
	return 0;
}