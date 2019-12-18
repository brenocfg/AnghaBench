#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  attinmeta; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_info; int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  char OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexTuple ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FuncCallContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int IndexInfoFindDataOffset (int /*<<< orphan*/ ) ; 
 scalar_t__ IndexTupleHasNulls (TYPE_1__*) ; 
 scalar_t__ IndexTupleHasVarwidths (TYPE_1__*) ; 
 int IndexTupleSize (TYPE_1__*) ; 
 int /*<<< orphan*/  ItemIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumberNoCheck (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumberNoCheck (int /*<<< orphan*/ *) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 char* palloc0 (int) ; 
 char* psprintf (char*,char,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

__attribute__((used)) static Datum
bt_page_print_tuples(FuncCallContext *fctx, Page page, OffsetNumber offset)
{
	char	   *values[6];
	HeapTuple	tuple;
	ItemId		id;
	IndexTuple	itup;
	int			j;
	int			off;
	int			dlen;
	char	   *dump;
	char	   *ptr;

	id = PageGetItemId(page, offset);

	if (!ItemIdIsValid(id))
		elog(ERROR, "invalid ItemId");

	itup = (IndexTuple) PageGetItem(page, id);

	j = 0;
	values[j++] = psprintf("%d", offset);
	values[j++] = psprintf("(%u,%u)",
						   ItemPointerGetBlockNumberNoCheck(&itup->t_tid),
						   ItemPointerGetOffsetNumberNoCheck(&itup->t_tid));
	values[j++] = psprintf("%d", (int) IndexTupleSize(itup));
	values[j++] = psprintf("%c", IndexTupleHasNulls(itup) ? 't' : 'f');
	values[j++] = psprintf("%c", IndexTupleHasVarwidths(itup) ? 't' : 'f');

	ptr = (char *) itup + IndexInfoFindDataOffset(itup->t_info);
	dlen = IndexTupleSize(itup) - IndexInfoFindDataOffset(itup->t_info);
	dump = palloc0(dlen * 3 + 1);
	values[j] = dump;
	for (off = 0; off < dlen; off++)
	{
		if (off > 0)
			*dump++ = ' ';
		sprintf(dump, "%02x", *(ptr + off) & 0xff);
		dump += 2;
	}

	tuple = BuildTupleFromCStrings(fctx->attinmeta, values);

	return HeapTupleGetDatum(tuple);
}