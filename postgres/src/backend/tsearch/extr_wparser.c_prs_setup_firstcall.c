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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_11__ {int /*<<< orphan*/  attinmeta; void* user_fctx; int /*<<< orphan*/  multi_call_memory_ctx; } ;
struct TYPE_10__ {char* lexeme; int type; } ;
struct TYPE_9__ {size_t cur; int len; TYPE_3__* list; } ;
struct TYPE_8__ {int /*<<< orphan*/  prsend; int /*<<< orphan*/  prstoken; int /*<<< orphan*/  prsstart; } ;
typedef  TYPE_1__ TSParserCacheEntry ;
typedef  TYPE_2__ PrsStorage ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__ LexemeEntry ;
typedef  TYPE_4__ FuncCallContext ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (void*) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TupleDescGetAttInMetadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 TYPE_1__* lookup_ts_parser_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* palloc (int) ; 
 scalar_t__ repalloc (TYPE_3__*,int) ; 

__attribute__((used)) static void
prs_setup_firstcall(FuncCallContext *funcctx, Oid prsid, text *txt)
{
	TupleDesc	tupdesc;
	MemoryContext oldcontext;
	PrsStorage *st;
	TSParserCacheEntry *prs = lookup_ts_parser_cache(prsid);
	char	   *lex = NULL;
	int			llen = 0,
				type = 0;
	void	   *prsdata;

	oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

	st = (PrsStorage *) palloc(sizeof(PrsStorage));
	st->cur = 0;
	st->len = 16;
	st->list = (LexemeEntry *) palloc(sizeof(LexemeEntry) * st->len);

	prsdata = (void *) DatumGetPointer(FunctionCall2(&prs->prsstart,
													 PointerGetDatum(VARDATA_ANY(txt)),
													 Int32GetDatum(VARSIZE_ANY_EXHDR(txt))));

	while ((type = DatumGetInt32(FunctionCall3(&prs->prstoken,
											   PointerGetDatum(prsdata),
											   PointerGetDatum(&lex),
											   PointerGetDatum(&llen)))) != 0)
	{
		if (st->cur >= st->len)
		{
			st->len = 2 * st->len;
			st->list = (LexemeEntry *) repalloc(st->list, sizeof(LexemeEntry) * st->len);
		}
		st->list[st->cur].lexeme = palloc(llen + 1);
		memcpy(st->list[st->cur].lexeme, lex, llen);
		st->list[st->cur].lexeme[llen] = '\0';
		st->list[st->cur].type = type;
		st->cur++;
	}

	FunctionCall1(&prs->prsend, PointerGetDatum(prsdata));

	st->len = st->cur;
	st->cur = 0;

	funcctx->user_fctx = (void *) st;
	tupdesc = CreateTemplateTupleDesc(2);
	TupleDescInitEntry(tupdesc, (AttrNumber) 1, "tokid",
					   INT4OID, -1, 0);
	TupleDescInitEntry(tupdesc, (AttrNumber) 2, "token",
					   TEXTOID, -1, 0);

	funcctx->attinmeta = TupleDescGetAttInMetadata(tupdesc);
	MemoryContextSwitchTo(oldcontext);
}