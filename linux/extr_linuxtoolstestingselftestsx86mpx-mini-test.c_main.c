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
 int /*<<< orphan*/  bd_incore () ; 
 int /*<<< orphan*/  check_bounds_table_frees () ; 
 int /*<<< orphan*/  check_mpx_support () ; 
 int /*<<< orphan*/  compare_context (scalar_t__) ; 
 int /*<<< orphan*/  exhaust_vaddr_space () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init () ; 
 int /*<<< orphan*/  mpx_prepare () ; 
 int /*<<< orphan*/  mpx_table_test () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  srandom (int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  trace_me () ; 
 int /*<<< orphan*/  xsave_state (void*,int) ; 
 scalar_t__ xsave_test_buf ; 

int main(int argc, char **argv)
{
	int unmaptest = 0;
	int vaddrexhaust = 0;
	int tabletest = 0;
	int i;

	check_mpx_support();
	mpx_prepare();
	srandom(11179);

	bd_incore();
	init();
	bd_incore();

	trace_me();

	xsave_state((void *)xsave_test_buf, 0x1f);
	if (!compare_context(xsave_test_buf))
		printf("Init failed\n");

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "unmaptest"))
			unmaptest = 1;
		if (!strcmp(argv[i], "vaddrexhaust"))
			vaddrexhaust = 1;
		if (!strcmp(argv[i], "tabletest"))
			tabletest = 1;
	}
	if (!(unmaptest || vaddrexhaust || tabletest)) {
		unmaptest = 1;
		/* vaddrexhaust = 1; */
		tabletest = 1;
	}
	if (unmaptest)
		check_bounds_table_frees();
	if (tabletest)
		mpx_table_test();
	if (vaddrexhaust)
		exhaust_vaddr_space();
	printf("%s completed successfully\n", argv[0]);
	exit(0);
}