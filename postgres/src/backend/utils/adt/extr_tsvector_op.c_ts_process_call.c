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
struct TYPE_6__ {int /*<<< orphan*/  attinmeta; scalar_t__ user_fctx; } ;
struct TYPE_5__ {int lenlexeme; int ndoc; int nentry; int /*<<< orphan*/  lexeme; } ;
typedef  int /*<<< orphan*/  TSVectorStat ;
typedef  TYPE_1__ StatEntry ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FuncCallContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* walkStatEntryTree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Datum
ts_process_call(FuncCallContext *funcctx)
{
	TSVectorStat *st;
	StatEntry  *entry;

	st = (TSVectorStat *) funcctx->user_fctx;

	entry = walkStatEntryTree(st);

	if (entry != NULL)
	{
		Datum		result;
		char	   *values[3];
		char		ndoc[16];
		char		nentry[16];
		HeapTuple	tuple;

		values[0] = palloc(entry->lenlexeme + 1);
		memcpy(values[0], entry->lexeme, entry->lenlexeme);
		(values[0])[entry->lenlexeme] = '\0';
		sprintf(ndoc, "%d", entry->ndoc);
		values[1] = ndoc;
		sprintf(nentry, "%d", entry->nentry);
		values[2] = nentry;

		tuple = BuildTupleFromCStrings(funcctx->attinmeta, values);
		result = HeapTupleGetDatum(tuple);

		pfree(values[0]);

		/* mark entry as already visited */
		entry->ndoc = 0;

		return result;
	}

	return (Datum) 0;
}