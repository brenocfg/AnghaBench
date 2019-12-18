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
struct lbuf {int l_pn; int l_flag; scalar_t__ l_blkno; } ;
struct jfs_log {int l2bsize; scalar_t__ base; } ;

/* Variables and functions */
 int L2LOGPSIZE ; 
 int /*<<< orphan*/  jfs_info (char*,struct lbuf*,int,int) ; 
 int lbmDIRECT ; 
 int /*<<< orphan*/  lbmStartIO (struct lbuf*) ; 

__attribute__((used)) static void lbmDirectWrite(struct jfs_log * log, struct lbuf * bp, int flag)
{
	jfs_info("lbmDirectWrite: bp:0x%p flag:0x%x pn:0x%x",
		 bp, flag, bp->l_pn);

	/*
	 * initialize buffer for device driver
	 */
	bp->l_flag = flag | lbmDIRECT;

	/* map the logical block address to physical block address */
	bp->l_blkno =
	    log->base + (bp->l_pn << (L2LOGPSIZE - log->l2bsize));

	/*
	 *	initiate pageout of the page
	 */
	lbmStartIO(bp);
}