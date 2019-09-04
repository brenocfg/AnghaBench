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
 int /*<<< orphan*/  SO_DEBUG ; 
 int atoi (char const*) ; 
 int code ; 
 int debug ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* onoff (int) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  stdout ; 

void setdebug(int argc, const char *argv[])
{
	int val;

	if (argc > 1) {
		val = atoi(argv[1]);
		if (val < 0) {
			printf("%s: bad debugging value.\n", argv[1]);
			(void) fflush(stdout);
			code = -1;
			return;
		}
	} else
		val = !debug;
	debug = val;
	if (debug)
		options |= SO_DEBUG;
	else
		options &= ~SO_DEBUG;
	printf("Debugging %s (debug=%d).\n", onoff(debug), debug);
	(void) fflush(stdout);
	code = debug > 0;
}