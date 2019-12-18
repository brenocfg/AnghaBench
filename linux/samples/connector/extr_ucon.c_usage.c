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
 int CN_TEST_IDX ; 
 int CN_TEST_VAL ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void usage(void)
{
	printf(
		"Usage: ucon [options] [output file]\n"
		"\n"
		"\t-h\tthis help screen\n"
		"\t-s\tsend buffers to the test module\n"
		"\n"
		"The default behavior of ucon is to subscribe to the test module\n"
		"and wait for state messages.  Any ones received are dumped to the\n"
		"specified output file (or stdout).  The test module is assumed to\n"
		"have an id of {%u.%u}\n"
		"\n"
		"If you get no output, then verify the cn_test module id matches\n"
		"the expected id above.\n"
		, CN_TEST_IDX, CN_TEST_VAL
	);
}