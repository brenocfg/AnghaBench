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
struct ldtentry {int namlen; int next; int /*<<< orphan*/  index; } ;
struct idtentry {int namlen; int next; int /*<<< orphan*/  index; } ;
struct dtslot {int next; int cnt; int /*<<< orphan*/  name; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
typedef  int s8 ;
struct TYPE_5__ {size_t stblindex; int freelist; int nextindex; int flag; int freecnt; } ;
struct TYPE_6__ {TYPE_1__ header; struct dtslot* slot; } ;
typedef  TYPE_2__ dtpage_t ;

/* Variables and functions */
 int BT_LEAF ; 
 int /*<<< orphan*/  DTIHDRDATALEN ; 
 int /*<<< orphan*/  DTLHDRDATALEN ; 
 int /*<<< orphan*/  DTLHDRDATALEN_LEGACY ; 
 int /*<<< orphan*/  DTSLOTDATALEN ; 
 int /*<<< orphan*/  UniStrncpy_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct ldtentry*,struct ldtentry*,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ txLinelock (struct dt_lock*) ; 

__attribute__((used)) static void dtMoveEntry(dtpage_t * sp, int si, dtpage_t * dp,
			struct dt_lock ** sdtlock, struct dt_lock ** ddtlock,
			int do_index)
{
	int ssi, next;		/* src slot index */
	int di;			/* dst entry index */
	int dsi;		/* dst slot index */
	s8 *sstbl, *dstbl;	/* sorted entry table */
	int snamlen, len;
	struct ldtentry *slh, *dlh = NULL;
	struct idtentry *sih, *dih = NULL;
	struct dtslot *h, *s, *d;
	struct dt_lock *sdtlck = *sdtlock, *ddtlck = *ddtlock;
	struct lv *slv, *dlv;
	int xssi, ns, nd;
	int sfsi;

	sstbl = (s8 *) & sp->slot[sp->header.stblindex];
	dstbl = (s8 *) & dp->slot[dp->header.stblindex];

	dsi = dp->header.freelist;	/* first (whole page) free slot */
	sfsi = sp->header.freelist;

	/* linelock destination entry slot */
	dlv = & ddtlck->lv[ddtlck->index];
	dlv->offset = dsi;

	/* linelock source entry slot */
	slv = & sdtlck->lv[sdtlck->index];
	slv->offset = sstbl[si];
	xssi = slv->offset - 1;

	/*
	 * move entries
	 */
	ns = nd = 0;
	for (di = 0; si < sp->header.nextindex; si++, di++) {
		ssi = sstbl[si];
		dstbl[di] = dsi;

		/* is next slot contiguous ? */
		if (ssi != xssi + 1) {
			/* close current linelock */
			slv->length = ns;
			sdtlck->index++;

			/* open new linelock */
			if (sdtlck->index < sdtlck->maxcnt)
				slv++;
			else {
				sdtlck = (struct dt_lock *) txLinelock(sdtlck);
				slv = & sdtlck->lv[0];
			}

			slv->offset = ssi;
			ns = 0;
		}

		/*
		 * move head/only segment of an entry
		 */
		/* get dst slot */
		h = d = &dp->slot[dsi];

		/* get src slot and move */
		s = &sp->slot[ssi];
		if (sp->header.flag & BT_LEAF) {
			/* get source entry */
			slh = (struct ldtentry *) s;
			dlh = (struct ldtentry *) h;
			snamlen = slh->namlen;

			if (do_index) {
				len = min(snamlen, DTLHDRDATALEN);
				dlh->index = slh->index; /* little-endian */
			} else
				len = min(snamlen, DTLHDRDATALEN_LEGACY);

			memcpy(dlh, slh, 6 + len * 2);

			next = slh->next;

			/* update dst head/only segment next field */
			dsi++;
			dlh->next = dsi;
		} else {
			sih = (struct idtentry *) s;
			snamlen = sih->namlen;

			len = min(snamlen, DTIHDRDATALEN);
			dih = (struct idtentry *) h;
			memcpy(dih, sih, 10 + len * 2);
			next = sih->next;

			dsi++;
			dih->next = dsi;
		}

		/* free src head/only segment */
		s->next = sfsi;
		s->cnt = 1;
		sfsi = ssi;

		ns++;
		nd++;
		xssi = ssi;

		/*
		 * move additional segment(s) of the entry
		 */
		snamlen -= len;
		while ((ssi = next) >= 0) {
			/* is next slot contiguous ? */
			if (ssi != xssi + 1) {
				/* close current linelock */
				slv->length = ns;
				sdtlck->index++;

				/* open new linelock */
				if (sdtlck->index < sdtlck->maxcnt)
					slv++;
				else {
					sdtlck =
					    (struct dt_lock *)
					    txLinelock(sdtlck);
					slv = & sdtlck->lv[0];
				}

				slv->offset = ssi;
				ns = 0;
			}

			/* get next source segment */
			s = &sp->slot[ssi];

			/* get next destination free slot */
			d++;

			len = min(snamlen, DTSLOTDATALEN);
			UniStrncpy_le(d->name, s->name, len);

			ns++;
			nd++;
			xssi = ssi;

			dsi++;
			d->next = dsi;

			/* free source segment */
			next = s->next;
			s->next = sfsi;
			s->cnt = 1;
			sfsi = ssi;

			snamlen -= len;
		}		/* end while */

		/* terminate dst last/only segment */
		if (h == d) {
			/* single segment entry */
			if (dp->header.flag & BT_LEAF)
				dlh->next = -1;
			else
				dih->next = -1;
		} else
			/* multi-segment entry */
			d->next = -1;
	}			/* end for */

	/* close current linelock */
	slv->length = ns;
	sdtlck->index++;
	*sdtlock = sdtlck;

	dlv->length = nd;
	ddtlck->index++;
	*ddtlock = ddtlck;

	/* update source header */
	sp->header.freelist = sfsi;
	sp->header.freecnt += nd;

	/* update destination header */
	dp->header.nextindex = di;

	dp->header.freelist = dsi;
	dp->header.freecnt -= nd;
}