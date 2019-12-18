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
 int /*<<< orphan*/  CMD_LEN_MAX ; 
 int REPLACE_STR ; 
 char* g_selpath ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,char*) ; 

__attribute__((used)) static void opstr(char *buf, char *op)
{
#ifdef __linux__
	snprintf(buf, CMD_LEN_MAX, "xargs -0 -a %s -%c {} %s {} .", g_selpath, REPLACE_STR, op);
#else
	snprintf(buf, CMD_LEN_MAX, "cat %s | xargs -0 -o -%c {} %s {} .", g_selpath, REPLACE_STR, op);
#endif
}