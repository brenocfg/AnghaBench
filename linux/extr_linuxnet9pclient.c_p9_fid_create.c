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
struct p9_qid {int dummy; } ;
struct p9_fid {int mode; scalar_t__ fid; int /*<<< orphan*/ * rdir; struct p9_client* clnt; int /*<<< orphan*/  uid; int /*<<< orphan*/  qid; } ;
struct p9_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  fids; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  P9_DEBUG_FID ; 
 scalar_t__ P9_NOFID ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int idr_alloc_u32 (int /*<<< orphan*/ *,struct p9_fid*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  kfree (struct p9_fid*) ; 
 struct p9_fid* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_client*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct p9_fid *p9_fid_create(struct p9_client *clnt)
{
	int ret;
	struct p9_fid *fid;

	p9_debug(P9_DEBUG_FID, "clnt %p\n", clnt);
	fid = kmalloc(sizeof(struct p9_fid), GFP_KERNEL);
	if (!fid)
		return NULL;

	memset(&fid->qid, 0, sizeof(struct p9_qid));
	fid->mode = -1;
	fid->uid = current_fsuid();
	fid->clnt = clnt;
	fid->rdir = NULL;
	fid->fid = 0;

	idr_preload(GFP_KERNEL);
	spin_lock_irq(&clnt->lock);
	ret = idr_alloc_u32(&clnt->fids, fid, &fid->fid, P9_NOFID - 1,
			    GFP_NOWAIT);
	spin_unlock_irq(&clnt->lock);
	idr_preload_end();

	if (!ret)
		return fid;

	kfree(fid);
	return NULL;
}