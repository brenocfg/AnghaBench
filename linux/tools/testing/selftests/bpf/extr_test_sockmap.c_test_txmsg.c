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
 int test_loop (int) ; 
 scalar_t__ txmsg_apply ; 
 scalar_t__ txmsg_cork ; 
 int txmsg_drop ; 
 int txmsg_ingress ; 
 int txmsg_noisy ; 
 int txmsg_pass ; 
 int txmsg_redir ; 
 int txmsg_redir_noisy ; 
 int txmsg_skb ; 

__attribute__((used)) static int test_txmsg(int cgrp)
{
	int err;

	txmsg_pass = txmsg_noisy = txmsg_redir_noisy = txmsg_drop = 0;
	txmsg_apply = txmsg_cork = 0;
	txmsg_ingress = txmsg_skb = 0;

	txmsg_pass = 1;
	err = test_loop(cgrp);
	txmsg_pass = 0;
	if (err)
		goto out;

	txmsg_redir = 1;
	err = test_loop(cgrp);
	txmsg_redir = 0;
	if (err)
		goto out;

	txmsg_drop = 1;
	err = test_loop(cgrp);
	txmsg_drop = 0;
	if (err)
		goto out;

	txmsg_redir = 1;
	txmsg_ingress = 1;
	err = test_loop(cgrp);
	txmsg_redir = 0;
	txmsg_ingress = 0;
	if (err)
		goto out;
out:
	txmsg_pass = 0;
	txmsg_redir = 0;
	txmsg_drop = 0;
	return err;
}