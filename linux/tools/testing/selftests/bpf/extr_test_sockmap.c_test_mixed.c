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
struct sockmap_options {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int test_send (struct sockmap_options*,int) ; 
 int txmsg_apply ; 
 int txmsg_cork ; 
 int txmsg_drop ; 
 scalar_t__ txmsg_end ; 
 scalar_t__ txmsg_end_push ; 
 int txmsg_noisy ; 
 int txmsg_pass ; 
 scalar_t__ txmsg_pop ; 
 int txmsg_redir ; 
 int txmsg_redir_noisy ; 
 scalar_t__ txmsg_start ; 
 scalar_t__ txmsg_start_pop ; 
 scalar_t__ txmsg_start_push ; 

__attribute__((used)) static int test_mixed(int cgrp)
{
	struct sockmap_options opt = {0};
	int err;

	txmsg_pass = txmsg_noisy = txmsg_redir_noisy = txmsg_drop = 0;
	txmsg_apply = txmsg_cork = 0;
	txmsg_start = txmsg_end = 0;
	txmsg_start_push = txmsg_end_push = 0;
	txmsg_start_pop = txmsg_pop = 0;

	/* Test small and large iov_count values with pass/redir/apply/cork */
	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 1;
	txmsg_cork = 0;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 0;
	txmsg_cork = 1;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 1;
	txmsg_cork = 1;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 1024;
	txmsg_cork = 0;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 0;
	txmsg_cork = 1024;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 1024;
	txmsg_cork = 1024;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_cork = 4096;
	txmsg_apply = 4096;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 1;
	txmsg_cork = 0;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 0;
	txmsg_cork = 1;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 1024;
	txmsg_cork = 0;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 0;
	txmsg_cork = 1024;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 1024;
	txmsg_cork = 1024;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_cork = 4096;
	txmsg_apply = 4096;
	err = test_send(&opt, cgrp);
	if (err)
		goto out;
out:
	return err;
}