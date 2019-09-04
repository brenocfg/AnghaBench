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
struct rpc_pipe_dir_head {int /*<<< orphan*/ * pdh_dentry; int /*<<< orphan*/  pdh_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void rpc_init_pipe_dir_head(struct rpc_pipe_dir_head *pdh)
{
	INIT_LIST_HEAD(&pdh->pdh_entries);
	pdh->pdh_dentry = NULL;
}