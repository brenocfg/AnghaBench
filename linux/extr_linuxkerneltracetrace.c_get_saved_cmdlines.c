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
struct TYPE_2__ {char* saved_cmdlines; } ;

/* Variables and functions */
 int TASK_COMM_LEN ; 
 TYPE_1__* savedcmd ; 

__attribute__((used)) static inline char *get_saved_cmdlines(int idx)
{
	return &savedcmd->saved_cmdlines[idx * TASK_COMM_LEN];
}