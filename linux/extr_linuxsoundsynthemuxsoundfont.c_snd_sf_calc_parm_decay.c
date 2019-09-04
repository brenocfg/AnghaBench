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

/* Variables and functions */
 int calc_parm_search (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decay_time_tbl ; 

int
snd_sf_calc_parm_decay(int msec)
{
	return calc_parm_search(msec, decay_time_tbl);
}