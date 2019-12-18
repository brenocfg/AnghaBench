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
struct tlock {int type; struct metapage* mp; scalar_t__ next; } ;
struct tblock {int /*<<< orphan*/  waitor; scalar_t__ next; } ;
struct metapage {int xflag; scalar_t__ lid; } ;
typedef  scalar_t__ lid_t ;

/* Variables and functions */
 int COMMIT_PAGE ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 int /*<<< orphan*/  TXN_WAKEUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct tlock* lid_to_tlock (scalar_t__) ; 
 int tlckBTROOT ; 

__attribute__((used)) static void txRelease(struct tblock * tblk)
{
	struct metapage *mp;
	lid_t lid;
	struct tlock *tlck;

	TXN_LOCK();

	for (lid = tblk->next; lid; lid = tlck->next) {
		tlck = lid_to_tlock(lid);
		if ((mp = tlck->mp) != NULL &&
		    (tlck->type & tlckBTROOT) == 0) {
			assert(mp->xflag & COMMIT_PAGE);
			mp->lid = 0;
		}
	}

	/*
	 * wakeup transactions waiting on a page locked
	 * by the current transaction
	 */
	TXN_WAKEUP(&tblk->waitor);

	TXN_UNLOCK();
}