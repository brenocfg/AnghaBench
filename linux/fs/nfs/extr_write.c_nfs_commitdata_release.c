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
struct nfs_commit_data {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_commit_free (struct nfs_commit_data*) ; 
 int /*<<< orphan*/  put_nfs_open_context (int /*<<< orphan*/ ) ; 

void nfs_commitdata_release(struct nfs_commit_data *data)
{
	put_nfs_open_context(data->context);
	nfs_commit_free(data);
}