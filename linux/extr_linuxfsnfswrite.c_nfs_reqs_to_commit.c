#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_commit_info {TYPE_1__* mds; } ;
struct TYPE_2__ {int /*<<< orphan*/  ncommit; } ;

/* Variables and functions */
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 

unsigned long
nfs_reqs_to_commit(struct nfs_commit_info *cinfo)
{
	return atomic_long_read(&cinfo->mds->ncommit);
}