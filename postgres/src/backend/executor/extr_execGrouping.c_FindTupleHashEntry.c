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
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  TYPE_1__* TupleHashTable ;
typedef  int /*<<< orphan*/  TupleHashEntry ;
struct TYPE_3__ {int /*<<< orphan*/  hashtab; int /*<<< orphan*/ * cur_eq_func; int /*<<< orphan*/ * in_hash_funcs; int /*<<< orphan*/ * inputslot; int /*<<< orphan*/  tempcxt; } ;
typedef  int /*<<< orphan*/ * MinimalTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  ExprState ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplehash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

TupleHashEntry
FindTupleHashEntry(TupleHashTable hashtable, TupleTableSlot *slot,
				   ExprState *eqcomp,
				   FmgrInfo *hashfunctions)
{
	TupleHashEntry entry;
	MemoryContext oldContext;
	MinimalTuple key;

	/* Need to run the hash functions in short-lived context */
	oldContext = MemoryContextSwitchTo(hashtable->tempcxt);

	/* Set up data needed by hash and match functions */
	hashtable->inputslot = slot;
	hashtable->in_hash_funcs = hashfunctions;
	hashtable->cur_eq_func = eqcomp;

	/* Search the hash table */
	key = NULL;					/* flag to reference inputslot */
	entry = tuplehash_lookup(hashtable->hashtab, key);
	MemoryContextSwitchTo(oldContext);

	return entry;
}