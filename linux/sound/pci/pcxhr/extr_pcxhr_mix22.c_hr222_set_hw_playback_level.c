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
struct pcxhr_mgr {int dummy; } ;

/* Variables and functions */
 unsigned short AKM_LEFT_LEVEL_CMD ; 
 unsigned short AKM_RIGHT_LEVEL_CMD ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 scalar_t__* g_hr222_p_level ; 
 int /*<<< orphan*/  hr222_config_akm (struct pcxhr_mgr*,unsigned short) ; 

__attribute__((used)) static int hr222_set_hw_playback_level(struct pcxhr_mgr *mgr,
				       int idx, int level)
{
	unsigned short cmd;
	if (idx > 1 ||
	    level < 0 ||
	    level >= ARRAY_SIZE(g_hr222_p_level))
		return -EINVAL;

	if (idx == 0)
		cmd = AKM_LEFT_LEVEL_CMD;
	else
		cmd = AKM_RIGHT_LEVEL_CMD;

	/* conversion from PmBoardCodedLevel to AKM nonlinear programming */
	cmd += g_hr222_p_level[level];

	hr222_config_akm(mgr, cmd);
	return 0;
}