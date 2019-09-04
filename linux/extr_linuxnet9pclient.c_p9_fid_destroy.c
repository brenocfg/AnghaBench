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
struct p9_fid {struct p9_fid* rdir; int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  fids; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FID ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void p9_fid_destroy(struct p9_fid *fid)
{
	struct p9_client *clnt;
	unsigned long flags;

	p9_debug(P9_DEBUG_FID, "fid %d\n", fid->fid);
	clnt = fid->clnt;
	spin_lock_irqsave(&clnt->lock, flags);
	idr_remove(&clnt->fids, fid->fid);
	spin_unlock_irqrestore(&clnt->lock, flags);
	kfree(fid->rdir);
	kfree(fid);
}