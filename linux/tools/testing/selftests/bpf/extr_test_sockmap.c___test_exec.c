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
struct sockmap_options {int sendpage; int drop_expected; int rate; int iov_count; int iov_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTSTRING ; 
 int SENDPAGE ; 
 char* calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  failed ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  passed ; 
 int run_options (struct sockmap_options*,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int test_cnt ; 
 int /*<<< orphan*/  test_options (char*) ; 
 char* test_to_str (int) ; 
 scalar_t__ txmsg_drop ; 

__attribute__((used)) static int __test_exec(int cgrp, int test, struct sockmap_options *opt)
{
	char *options = calloc(OPTSTRING, sizeof(char));
	int err;

	if (test == SENDPAGE)
		opt->sendpage = true;
	else
		opt->sendpage = false;

	if (txmsg_drop)
		opt->drop_expected = true;
	else
		opt->drop_expected = false;

	test_options(options);

	fprintf(stdout,
		"[TEST %i]: (%i, %i, %i, %s, %s): ",
		test_cnt, opt->rate, opt->iov_count, opt->iov_length,
		test_to_str(test), options);
	fflush(stdout);
	err = run_options(opt, cgrp, test);
	fprintf(stdout, "%s\n", !err ? "PASS" : "FAILED");
	test_cnt++;
	!err ? passed++ : failed++;
	free(options);
	return err;
}