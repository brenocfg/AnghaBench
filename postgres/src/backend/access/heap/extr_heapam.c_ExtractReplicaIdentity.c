#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_14__ {TYPE_1__* rd_rel; } ;
struct TYPE_13__ {int natts; } ;
struct TYPE_12__ {char relreplident; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 scalar_t__ HeapTupleHasExternal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INDEX_ATTR_BITMAP_IDENTITY_KEY ; 
 int MaxHeapAttributeNumber ; 
 char REPLICA_IDENTITY_FULL ; 
 char REPLICA_IDENTITY_NOTHING ; 
 TYPE_2__* RelationGetDescr (TYPE_3__*) ; 
 int /*<<< orphan*/ * RelationGetIndexAttrBitmap (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationIsLogicallyLogged (TYPE_3__*) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_is_member (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * heap_form_tuple (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * toast_flatten_tuple (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static HeapTuple
ExtractReplicaIdentity(Relation relation, HeapTuple tp, bool key_changed,
					   bool *copy)
{
	TupleDesc	desc = RelationGetDescr(relation);
	char		replident = relation->rd_rel->relreplident;
	Bitmapset  *idattrs;
	HeapTuple	key_tuple;
	bool		nulls[MaxHeapAttributeNumber];
	Datum		values[MaxHeapAttributeNumber];

	*copy = false;

	if (!RelationIsLogicallyLogged(relation))
		return NULL;

	if (replident == REPLICA_IDENTITY_NOTHING)
		return NULL;

	if (replident == REPLICA_IDENTITY_FULL)
	{
		/*
		 * When logging the entire old tuple, it very well could contain
		 * toasted columns. If so, force them to be inlined.
		 */
		if (HeapTupleHasExternal(tp))
		{
			*copy = true;
			tp = toast_flatten_tuple(tp, desc);
		}
		return tp;
	}

	/* if the key hasn't changed and we're only logging the key, we're done */
	if (!key_changed)
		return NULL;

	/* find out the replica identity columns */
	idattrs = RelationGetIndexAttrBitmap(relation,
										 INDEX_ATTR_BITMAP_IDENTITY_KEY);

	/*
	 * If there's no defined replica identity columns, treat as !key_changed.
	 * (This case should not be reachable from heap_update, since that should
	 * calculate key_changed accurately.  But heap_delete just passes constant
	 * true for key_changed, so we can hit this case in deletes.)
	 */
	if (bms_is_empty(idattrs))
		return NULL;

	/*
	 * Construct a new tuple containing only the replica identity columns,
	 * with nulls elsewhere.  While we're at it, assert that the replica
	 * identity columns aren't null.
	 */
	heap_deform_tuple(tp, desc, values, nulls);

	for (int i = 0; i < desc->natts; i++)
	{
		if (bms_is_member(i + 1 - FirstLowInvalidHeapAttributeNumber,
						  idattrs))
			Assert(!nulls[i]);
		else
			nulls[i] = true;
	}

	key_tuple = heap_form_tuple(desc, values, nulls);
	*copy = true;

	bms_free(idattrs);

	/*
	 * If the tuple, which by here only contains indexed columns, still has
	 * toasted columns, force them to be inlined. This is somewhat unlikely
	 * since there's limits on the size of indexed columns, so we don't
	 * duplicate toast_flatten_tuple()s functionality in the above loop over
	 * the indexed columns, even if it would be more efficient.
	 */
	if (HeapTupleHasExternal(key_tuple))
	{
		HeapTuple	oldtup = key_tuple;

		key_tuple = toast_flatten_tuple(oldtup, desc);
		heap_freetuple(oldtup);
	}

	return key_tuple;
}