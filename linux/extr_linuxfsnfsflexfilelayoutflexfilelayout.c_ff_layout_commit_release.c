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
struct nfs_commit_data {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_commit_record_layoutstats_done (int /*<<< orphan*/ *,struct nfs_commit_data*) ; 
 int /*<<< orphan*/  pnfs_generic_commit_release (void*) ; 

__attribute__((used)) static void ff_layout_commit_release(void *data)
{
	struct nfs_commit_data *cdata = data;

	ff_layout_commit_record_layoutstats_done(&cdata->task, cdata);
	pnfs_generic_commit_release(data);
}