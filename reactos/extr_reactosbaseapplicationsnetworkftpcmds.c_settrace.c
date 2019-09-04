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
 char* onoff (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int trace ; 

void settrace(int argc, const char *argv[])
{

	trace = !trace;
	printf("Packet tracing %s.\n", onoff(trace));
	(void) fflush(stdout);
	code = trace;
}