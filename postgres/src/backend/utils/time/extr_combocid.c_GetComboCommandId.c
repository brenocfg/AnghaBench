#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_10__ {size_t combocid; } ;
struct TYPE_9__ {size_t cmin; size_t cmax; } ;
struct TYPE_8__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
typedef  TYPE_1__ HASHCTL ;
typedef  size_t CommandId ;
typedef  TYPE_2__ ComboCidKeyData ;
typedef  int /*<<< orphan*/  ComboCidEntryData ;
typedef  TYPE_3__* ComboCidEntry ;

/* Variables and functions */
 int CCID_ARRAY_SIZE ; 
 int /*<<< orphan*/  CCID_HASH_SIZE ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 TYPE_2__* comboCids ; 
 int /*<<< orphan*/ * comboHash ; 
 int /*<<< orphan*/ * hash_create (char*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ repalloc (TYPE_2__*,int) ; 
 int sizeComboCids ; 
 int usedComboCids ; 

__attribute__((used)) static CommandId
GetComboCommandId(CommandId cmin, CommandId cmax)
{
	CommandId	combocid;
	ComboCidKeyData key;
	ComboCidEntry entry;
	bool		found;

	/*
	 * Create the hash table and array the first time we need to use combo
	 * cids in the transaction.
	 */
	if (comboHash == NULL)
	{
		HASHCTL		hash_ctl;

		/* Make array first; existence of hash table asserts array exists */
		comboCids = (ComboCidKeyData *)
			MemoryContextAlloc(TopTransactionContext,
							   sizeof(ComboCidKeyData) * CCID_ARRAY_SIZE);
		sizeComboCids = CCID_ARRAY_SIZE;
		usedComboCids = 0;

		memset(&hash_ctl, 0, sizeof(hash_ctl));
		hash_ctl.keysize = sizeof(ComboCidKeyData);
		hash_ctl.entrysize = sizeof(ComboCidEntryData);
		hash_ctl.hcxt = TopTransactionContext;

		comboHash = hash_create("Combo CIDs",
								CCID_HASH_SIZE,
								&hash_ctl,
								HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);
	}

	/*
	 * Grow the array if there's not at least one free slot.  We must do this
	 * before possibly entering a new hashtable entry, else failure to
	 * repalloc would leave a corrupt hashtable entry behind.
	 */
	if (usedComboCids >= sizeComboCids)
	{
		int			newsize = sizeComboCids * 2;

		comboCids = (ComboCidKeyData *)
			repalloc(comboCids, sizeof(ComboCidKeyData) * newsize);
		sizeComboCids = newsize;
	}

	/* Lookup or create a hash entry with the desired cmin/cmax */

	/* We assume there is no struct padding in ComboCidKeyData! */
	key.cmin = cmin;
	key.cmax = cmax;
	entry = (ComboCidEntry) hash_search(comboHash,
										(void *) &key,
										HASH_ENTER,
										&found);

	if (found)
	{
		/* Reuse an existing combo cid */
		return entry->combocid;
	}

	/* We have to create a new combo cid; we already made room in the array */
	combocid = usedComboCids;

	comboCids[combocid].cmin = cmin;
	comboCids[combocid].cmax = cmax;
	usedComboCids++;

	entry->combocid = combocid;

	return combocid;
}