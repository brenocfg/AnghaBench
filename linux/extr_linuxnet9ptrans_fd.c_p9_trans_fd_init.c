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
 int /*<<< orphan*/  p9_fd_trans ; 
 int /*<<< orphan*/  p9_tcp_trans ; 
 int /*<<< orphan*/  p9_unix_trans ; 
 int /*<<< orphan*/  v9fs_register_trans (int /*<<< orphan*/ *) ; 

int p9_trans_fd_init(void)
{
	v9fs_register_trans(&p9_tcp_trans);
	v9fs_register_trans(&p9_unix_trans);
	v9fs_register_trans(&p9_fd_trans);

	return 0;
}