#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  committed; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct nfs_direct_req {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; TYPE_1__ verf; TYPE_2__ mds_cinfo; int /*<<< orphan*/  completion; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_INVALID_STABLE_HOW ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct nfs_direct_req* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_direct_cachep ; 
 int /*<<< orphan*/  nfs_direct_write_schedule_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct nfs_direct_req *nfs_direct_req_alloc(void)
{
	struct nfs_direct_req *dreq;

	dreq = kmem_cache_zalloc(nfs_direct_cachep, GFP_KERNEL);
	if (!dreq)
		return NULL;

	kref_init(&dreq->kref);
	kref_get(&dreq->kref);
	init_completion(&dreq->completion);
	INIT_LIST_HEAD(&dreq->mds_cinfo.list);
	dreq->verf.committed = NFS_INVALID_STABLE_HOW;	/* not set yet */
	INIT_WORK(&dreq->work, nfs_direct_write_schedule_work);
	spin_lock_init(&dreq->lock);

	return dreq;
}