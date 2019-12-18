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
struct lbuf {int l_flag; int /*<<< orphan*/  l_ioevent; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LCACHE_LOCK (unsigned long) ; 
 int /*<<< orphan*/  LCACHE_SLEEP_COND (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  LCACHE_UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  jfs_info (char*,struct lbuf*,int,int) ; 
 int lbmDONE ; 
 int lbmERROR ; 
 int lbmFREE ; 
 int /*<<< orphan*/  lbmfree (struct lbuf*) ; 

__attribute__((used)) static int lbmIOWait(struct lbuf * bp, int flag)
{
	unsigned long flags;
	int rc = 0;

	jfs_info("lbmIOWait1: bp:0x%p flag:0x%x:0x%x", bp, bp->l_flag, flag);

	LCACHE_LOCK(flags);		/* disable+lock */

	LCACHE_SLEEP_COND(bp->l_ioevent, (bp->l_flag & lbmDONE), flags);

	rc = (bp->l_flag & lbmERROR) ? -EIO : 0;

	if (flag & lbmFREE)
		lbmfree(bp);

	LCACHE_UNLOCK(flags);	/* unlock+enable */

	jfs_info("lbmIOWait2: bp:0x%p flag:0x%x:0x%x", bp, bp->l_flag, flag);
	return rc;
}