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
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_fd_trans ; 
 int /*<<< orphan*/  p9_poll_work ; 
 int /*<<< orphan*/  p9_tcp_trans ; 
 int /*<<< orphan*/  p9_unix_trans ; 
 int /*<<< orphan*/  v9fs_unregister_trans (int /*<<< orphan*/ *) ; 

void p9_trans_fd_exit(void)
{
	flush_work(&p9_poll_work);
	v9fs_unregister_trans(&p9_tcp_trans);
	v9fs_unregister_trans(&p9_unix_trans);
	v9fs_unregister_trans(&p9_fd_trans);
}