#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lv {int offset; int length; } ;
struct dtslot {int next; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
struct TYPE_4__ {int freelist; } ;
struct TYPE_5__ {struct dtslot* slot; TYPE_1__ header; } ;
typedef  TYPE_2__ dtpage_t ;

/* Variables and functions */
 scalar_t__ txLinelock (struct dt_lock*) ; 

__attribute__((used)) static void dtLinelockFreelist(dtpage_t * p,	/* directory page */
			       int m,	/* max slot index */
			       struct dt_lock ** dtlock)
{
	int fsi;		/* free entry slot index */
	struct dtslot *t;
	int si;
	struct dt_lock *dtlck = *dtlock;
	struct lv *lv;
	int xsi, n;

	/* get free entry slot index */
	fsi = p->header.freelist;

	/* open new linelock */
	if (dtlck->index >= dtlck->maxcnt)
		dtlck = (struct dt_lock *) txLinelock(dtlck);
	lv = & dtlck->lv[dtlck->index];

	lv->offset = fsi;

	n = 1;
	xsi = fsi;

	t = &p->slot[fsi];
	si = t->next;

	/* find the last/only segment */
	while (si < m && si >= 0) {
		/* is next slot contiguous ? */
		if (si != xsi + 1) {
			/* close current linelock */
			lv->length = n;
			dtlck->index++;

			/* open new linelock */
			if (dtlck->index < dtlck->maxcnt)
				lv++;
			else {
				dtlck = (struct dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			}

			lv->offset = si;
			n = 0;
		}

		n++;
		xsi = si;

		t = &p->slot[si];
		si = t->next;
	}

	/* close current linelock */
	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;
}