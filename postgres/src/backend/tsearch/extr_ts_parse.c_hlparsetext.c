#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  vectorpos; } ;
struct TYPE_10__ {int /*<<< orphan*/  prsId; } ;
struct TYPE_9__ {int /*<<< orphan*/  prsend; int /*<<< orphan*/  prstoken; int /*<<< orphan*/  prsstart; } ;
typedef  int /*<<< orphan*/  TSQuery ;
typedef  TYPE_1__ TSParserCacheEntry ;
typedef  int /*<<< orphan*/  TSLexeme ;
typedef  TYPE_2__ TSConfigCacheEntry ;
typedef  int /*<<< orphan*/  ParsedLex ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LexizeData ;
typedef  TYPE_3__ HeadlineParsedText ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  LexizeAddLemm (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/ * LexizeExec (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LexizeInit (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int MAXSTRLEN ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  PointerGetDatum (void*) ; 
 int /*<<< orphan*/  addHLParsedLex (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_2__* lookup_ts_config_cache (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_ts_parser_cache (int /*<<< orphan*/ ) ; 

void
hlparsetext(Oid cfgId, HeadlineParsedText *prs, TSQuery query, char *buf, int buflen)
{
	int			type,
				lenlemm;
	char	   *lemm = NULL;
	LexizeData	ldata;
	TSLexeme   *norms;
	ParsedLex  *lexs;
	TSConfigCacheEntry *cfg;
	TSParserCacheEntry *prsobj;
	void	   *prsdata;

	cfg = lookup_ts_config_cache(cfgId);
	prsobj = lookup_ts_parser_cache(cfg->prsId);

	prsdata = (void *) DatumGetPointer(FunctionCall2(&(prsobj->prsstart),
													 PointerGetDatum(buf),
													 Int32GetDatum(buflen)));

	LexizeInit(&ldata, cfg);

	do
	{
		type = DatumGetInt32(FunctionCall3(&(prsobj->prstoken),
										   PointerGetDatum(prsdata),
										   PointerGetDatum(&lemm),
										   PointerGetDatum(&lenlemm)));

		if (type > 0 && lenlemm >= MAXSTRLEN)
		{
#ifdef IGNORE_LONGLEXEME
			ereport(NOTICE,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("word is too long to be indexed"),
					 errdetail("Words longer than %d characters are ignored.",
							   MAXSTRLEN)));
			continue;
#else
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("word is too long to be indexed"),
					 errdetail("Words longer than %d characters are ignored.",
							   MAXSTRLEN)));
#endif
		}

		LexizeAddLemm(&ldata, type, lemm, lenlemm);

		do
		{
			if ((norms = LexizeExec(&ldata, &lexs)) != NULL)
			{
				prs->vectorpos++;
				addHLParsedLex(prs, query, lexs, norms);
			}
			else
				addHLParsedLex(prs, query, lexs, NULL);
		} while (norms);

	} while (type > 0);

	FunctionCall1(&(prsobj->prsend), PointerGetDatum(prsdata));
}