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
struct tlock {int flag; } ;
struct linelock {int flag; scalar_t__ next; scalar_t__ index; int /*<<< orphan*/  maxcnt; } ;
typedef  scalar_t__ lid_t ;

/* Variables and functions */
 int /*<<< orphan*/  TLOCKLONG ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 struct tlock* lid_to_tlock (scalar_t__) ; 
 int tlckDIRECTORY ; 
 int tlckLINELOCK ; 
 scalar_t__ txLockAlloc () ; 

struct linelock *txLinelock(struct linelock * tlock)
{
	lid_t lid;
	struct tlock *tlck;
	struct linelock *linelock;

	TXN_LOCK();

	/* allocate a TxLock structure */
	lid = txLockAlloc();
	tlck = lid_to_tlock(lid);

	TXN_UNLOCK();

	/* initialize linelock */
	linelock = (struct linelock *) tlck;
	linelock->next = 0;
	linelock->flag = tlckLINELOCK;
	linelock->maxcnt = TLOCKLONG;
	linelock->index = 0;
	if (tlck->flag & tlckDIRECTORY)
		linelock->flag |= tlckDIRECTORY;

	/* append linelock after tlock */
	linelock->next = tlock->next;
	tlock->next = lid;

	return linelock;
}