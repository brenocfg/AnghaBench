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
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_commit_end(struct nfs_mds_commit_info *cinfo)
{
	if (atomic_dec_and_test(&cinfo->rpcs_out))
		wake_up_var(&cinfo->rpcs_out);
}