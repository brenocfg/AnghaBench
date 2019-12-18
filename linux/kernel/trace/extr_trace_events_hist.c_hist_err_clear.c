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
 char* last_cmd ; 
 char* last_cmd_loc ; 

__attribute__((used)) static void hist_err_clear(void)
{
	last_cmd[0] = '\0';
	last_cmd_loc[0] = '\0';
}