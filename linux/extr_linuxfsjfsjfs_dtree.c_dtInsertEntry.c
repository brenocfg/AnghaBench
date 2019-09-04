#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct metapage {int dummy; } ;
struct lv {int offset; int length; } ;
struct ldtentry {int next; int namlen; void* index; int /*<<< orphan*/ * name; void* inumber; } ;
struct idtentry {int next; int namlen; int /*<<< orphan*/ * name; } ;
struct dtslot {int next; int /*<<< orphan*/ * name; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
struct component_name {int namlen; int /*<<< orphan*/ * name; } ;
typedef  size_t s8 ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_9__ {int freelist; int flag; int nextindex; int /*<<< orphan*/  freecnt; int /*<<< orphan*/  self; } ;
struct TYPE_10__ {TYPE_2__ header; struct dtslot* slot; } ;
typedef  TYPE_3__ dtpage_t ;
struct TYPE_8__ {scalar_t__ ip; int /*<<< orphan*/  tid; int /*<<< orphan*/  ino; } ;
struct TYPE_11__ {TYPE_1__ leaf; int /*<<< orphan*/  xd; } ;
typedef  TYPE_4__ ddata_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int BT_LEAF ; 
 int BT_ROOT ; 
 int /*<<< orphan*/  DTIHDRDATALEN ; 
 int /*<<< orphan*/  DTLHDRDATALEN ; 
 int /*<<< orphan*/  DTLHDRDATALEN_LEGACY ; 
 int /*<<< orphan*/  DTSLOTDATALEN ; 
 size_t* DT_GETSTBL (TYPE_3__*) ; 
 int /*<<< orphan*/  UniStrncpy_to_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_index (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  addressPXD (int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memmove (size_t*,size_t*,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_index (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct metapage**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 scalar_t__ txLinelock (struct dt_lock*) ; 

__attribute__((used)) static void dtInsertEntry(dtpage_t * p, int index, struct component_name * key,
			  ddata_t * data, struct dt_lock ** dtlock)
{
	struct dtslot *h, *t;
	struct ldtentry *lh = NULL;
	struct idtentry *ih = NULL;
	int hsi, fsi, klen, len, nextindex;
	wchar_t *kname;
	__le16 *name;
	s8 *stbl;
	pxd_t *xd;
	struct dt_lock *dtlck = *dtlock;
	struct lv *lv;
	int xsi, n;
	s64 bn = 0;
	struct metapage *mp = NULL;

	klen = key->namlen;
	kname = key->name;

	/* allocate a free slot */
	hsi = fsi = p->header.freelist;
	h = &p->slot[fsi];
	p->header.freelist = h->next;
	--p->header.freecnt;

	/* open new linelock */
	if (dtlck->index >= dtlck->maxcnt)
		dtlck = (struct dt_lock *) txLinelock(dtlck);

	lv = & dtlck->lv[dtlck->index];
	lv->offset = hsi;

	/* write head/only segment */
	if (p->header.flag & BT_LEAF) {
		lh = (struct ldtentry *) h;
		lh->next = h->next;
		lh->inumber = cpu_to_le32(data->leaf.ino);
		lh->namlen = klen;
		name = lh->name;
		if (data->leaf.ip) {
			len = min(klen, DTLHDRDATALEN);
			if (!(p->header.flag & BT_ROOT))
				bn = addressPXD(&p->header.self);
			lh->index = cpu_to_le32(add_index(data->leaf.tid,
							  data->leaf.ip,
							  bn, index));
		} else
			len = min(klen, DTLHDRDATALEN_LEGACY);
	} else {
		ih = (struct idtentry *) h;
		ih->next = h->next;
		xd = (pxd_t *) ih;
		*xd = data->xd;
		ih->namlen = klen;
		name = ih->name;
		len = min(klen, DTIHDRDATALEN);
	}

	UniStrncpy_to_le(name, kname, len);

	n = 1;
	xsi = hsi;

	/* write additional segment(s) */
	t = h;
	klen -= len;
	while (klen) {
		/* get free slot */
		fsi = p->header.freelist;
		t = &p->slot[fsi];
		p->header.freelist = t->next;
		--p->header.freecnt;

		/* is next slot contiguous ? */
		if (fsi != xsi + 1) {
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

			lv->offset = fsi;
			n = 0;
		}

		kname += len;
		len = min(klen, DTSLOTDATALEN);
		UniStrncpy_to_le(t->name, kname, len);

		n++;
		xsi = fsi;
		klen -= len;
	}

	/* close current linelock */
	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;

	/* terminate last/only segment */
	if (h == t) {
		/* single segment entry */
		if (p->header.flag & BT_LEAF)
			lh->next = -1;
		else
			ih->next = -1;
	} else
		/* multi-segment entry */
		t->next = -1;

	/* if insert into middle, shift right succeeding entries in stbl */
	stbl = DT_GETSTBL(p);
	nextindex = p->header.nextindex;
	if (index < nextindex) {
		memmove(stbl + index + 1, stbl + index, nextindex - index);

		if ((p->header.flag & BT_LEAF) && data->leaf.ip) {
			s64 lblock;

			/*
			 * Need to update slot number for entries that moved
			 * in the stbl
			 */
			mp = NULL;
			for (n = index + 1; n <= nextindex; n++) {
				lh = (struct ldtentry *) & (p->slot[stbl[n]]);
				modify_index(data->leaf.tid, data->leaf.ip,
					     le32_to_cpu(lh->index), bn, n,
					     &mp, &lblock);
			}
			if (mp)
				release_metapage(mp);
		}
	}

	stbl[index] = hsi;

	/* advance next available entry index of stbl */
	++p->header.nextindex;
}