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
 int code ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int interactive ; 
 char* onoff (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

void setprompt(int argc, const char *argv[])
{

	interactive = !interactive;
	printf("Interactive mode %s.\n", onoff(interactive));
	(void) fflush(stdout);
	code = interactive;
}