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
struct sockmap_options {int base; int sendpage; int data_test; int drop_expected; int iov_count; int iov_length; int rate; scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  sched_yield () ; 
 int test_exec (int,struct sockmap_options*) ; 

__attribute__((used)) static int test_loop(int cgrp)
{
	struct sockmap_options opt;

	int err, i, l, r;

	opt.verbose = 0;
	opt.base = false;
	opt.sendpage = false;
	opt.data_test = false;
	opt.drop_expected = false;
	opt.iov_count = 0;
	opt.iov_length = 0;
	opt.rate = 0;

	r = 1;
	for (i = 1; i < 100; i += 33) {
		for (l = 1; l < 100; l += 33) {
			opt.rate = r;
			opt.iov_count = i;
			opt.iov_length = l;
			err = test_exec(cgrp, &opt);
			if (err)
				goto out;
		}
	}
	sched_yield();
out:
	return err;
}