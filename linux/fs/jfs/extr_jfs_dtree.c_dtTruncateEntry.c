#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lv {int offset; int length; } ;
struct idtentry {int next; scalar_t__ namlen; } ;
struct dtslot {int cnt; int next; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
typedef  int s8 ;
struct TYPE_5__ {int flag; int freelist; int freecnt; } ;
struct TYPE_6__ {TYPE_1__ header; struct dtslot* slot; } ;
typedef  TYPE_2__ dtpage_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BT_INTERNAL ; 
 int* DT_GETSTBL (TYPE_2__*) ; 
 scalar_t__ txLinelock (struct dt_lock*) ; 

__attribute__((used)) static void dtTruncateEntry(dtpage_t * p, int ti, struct dt_lock ** dtlock)
{
	int tsi;		/* truncate entry slot index */
	s8 *stbl;
	struct dtslot *t;
	int si, freecnt;
	struct dt_lock *dtlck = *dtlock;
	struct lv *lv;
	int fsi, xsi, n;

	/* get free entry slot index */
	stbl = DT_GETSTBL(p);
	tsi = stbl[ti];

	/* open new linelock */
	if (dtlck->index >= dtlck->maxcnt)
		dtlck = (struct dt_lock *) txLinelock(dtlck);
	lv = & dtlck->lv[dtlck->index];

	lv->offset = tsi;

	/* get the head/only segment */
	t = &p->slot[tsi];
	ASSERT(p->header.flag & BT_INTERNAL);
	((struct idtentry *) t)->namlen = 0;
	si = ((struct idtentry *) t)->next;
	((struct idtentry *) t)->next = -1;

	n = 1;
	freecnt = 0;
	fsi = si;
	xsi = tsi;

	/* find the last/only segment */
	while (si >= 0) {
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
		freecnt++;

		t = &p->slot[si];
		t->cnt = 1;
		si = t->next;
	}

	/* close current linelock */
	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;

	/* update freelist */
	if (freecnt == 0)
		return;
	t->next = p->header.freelist;
	p->header.freelist = fsi;
	p->header.freecnt += freecnt;
}