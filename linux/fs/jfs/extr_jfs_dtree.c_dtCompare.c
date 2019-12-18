#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct idtentry {int next; int namlen; int /*<<< orphan*/ * name; } ;
struct dtslot {int next; int /*<<< orphan*/ * name; } ;
struct component_name {int namlen; int /*<<< orphan*/ * name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * slot; } ;
typedef  TYPE_1__ dtpage_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int DTIHDRDATALEN ; 
 int DTSLOTDATALEN ; 
 int UniStrncmp_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int dtCompare(struct component_name * key,	/* search key */
		     dtpage_t * p,	/* directory page */
		     int si)
{				/* entry slot index */
	wchar_t *kname;
	__le16 *name;
	int klen, namlen, len, rc;
	struct idtentry *ih;
	struct dtslot *t;

	/*
	 * force the left-most key on internal pages, at any level of
	 * the tree, to be less than any search key.
	 * this obviates having to update the leftmost key on an internal
	 * page when the user inserts a new key in the tree smaller than
	 * anything that has been stored.
	 *
	 * (? if/when dtSearch() narrows down to 1st entry (index = 0),
	 * at any internal page at any level of the tree,
	 * it descends to child of the entry anyway -
	 * ? make the entry as min size dummy entry)
	 *
	 * if (e->index == 0 && h->prevpg == P_INVALID && !(h->flags & BT_LEAF))
	 * return (1);
	 */

	kname = key->name;
	klen = key->namlen;

	ih = (struct idtentry *) & p->slot[si];
	si = ih->next;
	name = ih->name;
	namlen = ih->namlen;
	len = min(namlen, DTIHDRDATALEN);

	/* compare with head/only segment */
	len = min(klen, len);
	if ((rc = UniStrncmp_le(kname, name, len)))
		return rc;

	klen -= len;
	namlen -= len;

	/* compare with additional segment(s) */
	kname += len;
	while (klen > 0 && namlen > 0) {
		/* compare with next name segment */
		t = (struct dtslot *) & p->slot[si];
		len = min(namlen, DTSLOTDATALEN);
		len = min(klen, len);
		name = t->name;
		if ((rc = UniStrncmp_le(kname, name, len)))
			return rc;

		klen -= len;
		namlen -= len;
		kname += len;
		si = t->next;
	}

	return (klen - namlen);
}