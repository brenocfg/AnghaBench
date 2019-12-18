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
typedef  int u32 ;
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {scalar_t__ lock; } ;
struct metapage {int dummy; } ;
struct lv {int offset; int length; } ;
struct linelock {size_t index; size_t maxcnt; struct lv* lv; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlckDATA ; 
 struct linelock* txLinelock (struct linelock*) ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lock_index(tid_t tid, struct inode *ip, struct metapage * mp,
			      u32 index)
{
	struct tlock *tlck;
	struct linelock *llck;
	struct lv *lv;

	tlck = txLock(tid, ip, mp, tlckDATA);
	llck = (struct linelock *) tlck->lock;

	if (llck->index >= llck->maxcnt)
		llck = txLinelock(llck);
	lv = &llck->lv[llck->index];

	/*
	 *	Linelock slot size is twice the size of directory table
	 *	slot size.  512 entries per page.
	 */
	lv->offset = ((index - 2) & 511) >> 1;
	lv->length = 1;
	llck->index++;
}