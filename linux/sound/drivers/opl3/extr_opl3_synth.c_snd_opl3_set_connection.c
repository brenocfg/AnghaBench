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
struct snd_opl3 {scalar_t__ fm_mode; int /*<<< orphan*/  (* command ) (struct snd_opl3*,int,unsigned char) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int OPL3_LEFT_4OP_0 ; 
 int OPL3_LEFT_4OP_1 ; 
 int OPL3_LEFT_4OP_2 ; 
 int OPL3_REG_CONNECTION_SELECT ; 
 int OPL3_RIGHT ; 
 int OPL3_RIGHT_4OP_0 ; 
 int OPL3_RIGHT_4OP_1 ; 
 int OPL3_RIGHT_4OP_2 ; 
 scalar_t__ SNDRV_DM_FM_MODE_OPL3 ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,int,unsigned char) ; 

__attribute__((used)) static int snd_opl3_set_connection(struct snd_opl3 * opl3, int connection)
{
	unsigned char reg_val;

	/* OPL-3 only */
	if (opl3->fm_mode != SNDRV_DM_FM_MODE_OPL3)
		return -EINVAL;

	reg_val = connection & (OPL3_RIGHT_4OP_0 | OPL3_RIGHT_4OP_1 | OPL3_RIGHT_4OP_2 |
				OPL3_LEFT_4OP_0 | OPL3_LEFT_4OP_1 | OPL3_LEFT_4OP_2);
	/* Set 4-op connections */
	opl3->command(opl3, OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT, reg_val);

	return 0;
}