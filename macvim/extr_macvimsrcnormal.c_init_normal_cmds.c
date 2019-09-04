#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cmd_char; } ;

/* Variables and functions */
 scalar_t__ NV_CMDS_SIZE ; 
 size_t* nv_cmd_idx ; 
 TYPE_1__* nv_cmds ; 
 int /*<<< orphan*/  nv_compare ; 
 int nv_max_linear ; 
 int /*<<< orphan*/  qsort (void*,size_t,int,int /*<<< orphan*/ ) ; 

void
init_normal_cmds()
{
    int		i;

    /* Fill the index table with a one to one relation. */
    for (i = 0; i < (int)NV_CMDS_SIZE; ++i)
	nv_cmd_idx[i] = i;

    /* Sort the commands by the command character.  */
    qsort((void *)&nv_cmd_idx, (size_t)NV_CMDS_SIZE, sizeof(short), nv_compare);

    /* Find the first entry that can't be indexed by the command character. */
    for (i = 0; i < (int)NV_CMDS_SIZE; ++i)
	if (i != nv_cmds[nv_cmd_idx[i]].cmd_char)
	    break;
    nv_max_linear = i - 1;
}