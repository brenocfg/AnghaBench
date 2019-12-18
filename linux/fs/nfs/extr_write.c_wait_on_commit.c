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
struct nfs_mds_commit_info {int /*<<< orphan*/  rpcs_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int wait_var_event_killable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wait_on_commit(struct nfs_mds_commit_info *cinfo)
{
	return wait_var_event_killable(&cinfo->rpcs_out,
				       !atomic_read(&cinfo->rpcs_out));
}