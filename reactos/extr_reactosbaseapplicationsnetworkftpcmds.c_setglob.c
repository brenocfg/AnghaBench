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
 int doglob ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* onoff (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

void setglob(int argc, const char *argv[])
{

	doglob = !doglob;
	printf("Globbing %s.\n", onoff(doglob));
	(void) fflush(stdout);
	code = doglob;
}