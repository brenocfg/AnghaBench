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
struct snd_opl3 {scalar_t__ hardware; int fm_mode; int /*<<< orphan*/  (* command ) (struct snd_opl3*,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OPL3_HW_OPL3 ; 
 int OPL3_REG_CONNECTION_SELECT ; 
 int OPL3_RIGHT ; 
 int SNDRV_DM_FM_MODE_OPL3 ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,int,int) ; 

__attribute__((used)) static int snd_opl3_set_mode(struct snd_opl3 * opl3, int mode)
{
	if ((mode == SNDRV_DM_FM_MODE_OPL3) && (opl3->hardware < OPL3_HW_OPL3))
		return -EINVAL;

	opl3->fm_mode = mode;
	if (opl3->hardware >= OPL3_HW_OPL3)
		opl3->command(opl3, OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT, 0x00);	/* Clear 4-op connections */

	return 0;
}