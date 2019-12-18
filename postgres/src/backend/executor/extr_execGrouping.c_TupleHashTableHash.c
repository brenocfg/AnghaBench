#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct tuplehash_hash {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  TYPE_1__* TupleHashTable ;
struct TYPE_2__ {int numCols; int hash_iv; int /*<<< orphan*/ * tab_collations; int /*<<< orphan*/ * tab_hash_funcs; int /*<<< orphan*/ * tableslot; int /*<<< orphan*/ * in_hash_funcs; int /*<<< orphan*/ * inputslot; int /*<<< orphan*/ * keyColIdx; } ;
typedef  int /*<<< orphan*/ * MinimalTuple ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecStoreMinimalTuple (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FunctionCall1Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int murmurhash32 (int) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static uint32
TupleHashTableHash(struct tuplehash_hash *tb, const MinimalTuple tuple)
{
	TupleHashTable hashtable = (TupleHashTable) tb->private_data;
	int			numCols = hashtable->numCols;
	AttrNumber *keyColIdx = hashtable->keyColIdx;
	uint32		hashkey = hashtable->hash_iv;
	TupleTableSlot *slot;
	FmgrInfo   *hashfunctions;
	int			i;

	if (tuple == NULL)
	{
		/* Process the current input tuple for the table */
		slot = hashtable->inputslot;
		hashfunctions = hashtable->in_hash_funcs;
	}
	else
	{
		/*
		 * Process a tuple already stored in the table.
		 *
		 * (this case never actually occurs due to the way simplehash.h is
		 * used, as the hash-value is stored in the entries)
		 */
		slot = hashtable->tableslot;
		ExecStoreMinimalTuple(tuple, slot, false);
		hashfunctions = hashtable->tab_hash_funcs;
	}

	for (i = 0; i < numCols; i++)
	{
		AttrNumber	att = keyColIdx[i];
		Datum		attr;
		bool		isNull;

		/* rotate hashkey left 1 bit at each step */
		hashkey = (hashkey << 1) | ((hashkey & 0x80000000) ? 1 : 0);

		attr = slot_getattr(slot, att, &isNull);

		if (!isNull)			/* treat nulls as having hash key 0 */
		{
			uint32		hkey;

			hkey = DatumGetUInt32(FunctionCall1Coll(&hashfunctions[i],
													hashtable->tab_collations[i],
													attr));
			hashkey ^= hkey;
		}
	}

	/*
	 * The way hashes are combined above, among each other and with the IV,
	 * doesn't lead to good bit perturbation. As the IV's goal is to lead to
	 * achieve that, perform a round of hashing of the combined hash -
	 * resulting in near perfect perturbation.
	 */
	return murmurhash32(hashkey);
}