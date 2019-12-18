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
struct pnfs_ds_commit_info {int nbuckets; struct pnfs_commit_bucket* buckets; } ;
struct pnfs_commit_bucket {int /*<<< orphan*/  committing; } ;
struct nfs_commit_info {struct pnfs_ds_commit_info* ds; } ;
struct nfs_commit_data {int ds_commit_index; int /*<<< orphan*/  pages; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct nfs_commit_data* nfs_commitdata_alloc (int) ; 
 int /*<<< orphan*/  pnfs_generic_retry_commit (struct nfs_commit_info*,int) ; 

__attribute__((used)) static unsigned int
pnfs_generic_alloc_ds_commits(struct nfs_commit_info *cinfo,
			      struct list_head *list)
{
	struct pnfs_ds_commit_info *fl_cinfo;
	struct pnfs_commit_bucket *bucket;
	struct nfs_commit_data *data;
	int i;
	unsigned int nreq = 0;

	fl_cinfo = cinfo->ds;
	bucket = fl_cinfo->buckets;
	for (i = 0; i < fl_cinfo->nbuckets; i++, bucket++) {
		if (list_empty(&bucket->committing))
			continue;
		data = nfs_commitdata_alloc(false);
		if (!data)
			break;
		data->ds_commit_index = i;
		list_add(&data->pages, list);
		nreq++;
	}

	/* Clean up on error */
	pnfs_generic_retry_commit(cinfo, i);
	return nreq;
}