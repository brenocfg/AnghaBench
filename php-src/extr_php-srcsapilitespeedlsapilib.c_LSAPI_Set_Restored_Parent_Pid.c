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
 int s_ppid ; 
 int s_restored_ppid ; 

int LSAPI_Set_Restored_Parent_Pid(int pid)
{
    int old_ppid = s_ppid;
    s_restored_ppid = pid;
    return old_ppid;
}