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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int LH_BUCKET_PAGE ; 
 int LH_OVERFLOW_PAGE ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_binsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_checkpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_get_indextuple_hashkey (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
_hash_pgaddmultitup(Relation rel, Buffer buf, IndexTuple *itups,
					OffsetNumber *itup_offsets, uint16 nitups)
{
	OffsetNumber itup_off;
	Page		page;
	uint32		hashkey;
	int			i;

	_hash_checkpage(rel, buf, LH_BUCKET_PAGE | LH_OVERFLOW_PAGE);
	page = BufferGetPage(buf);

	for (i = 0; i < nitups; i++)
	{
		Size		itemsize;

		itemsize = IndexTupleSize(itups[i]);
		itemsize = MAXALIGN(itemsize);

		/* Find where to insert the tuple (preserving page's hashkey ordering) */
		hashkey = _hash_get_indextuple_hashkey(itups[i]);
		itup_off = _hash_binsearch(page, hashkey);

		itup_offsets[i] = itup_off;

		if (PageAddItem(page, (Item) itups[i], itemsize, itup_off, false, false)
			== InvalidOffsetNumber)
			elog(ERROR, "failed to add index item to \"%s\"",
				 RelationGetRelationName(rel));
	}
}