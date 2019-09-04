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
struct sockmap_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SENDMSG ; 
 int /*<<< orphan*/  SENDPAGE ; 
 int __test_exec (int,int /*<<< orphan*/ ,struct sockmap_options*) ; 

__attribute__((used)) static int test_exec(int cgrp, struct sockmap_options *opt)
{
	int err = __test_exec(cgrp, SENDMSG, opt);

	if (err)
		goto out;

	err = __test_exec(cgrp, SENDPAGE, opt);
out:
	return err;
}