#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {size_t curwords; size_t lenwords; int /*<<< orphan*/  pos; TYPE_5__* words; } ;
struct TYPE_13__ {int /*<<< orphan*/  pos; } ;
struct TYPE_17__ {int flags; TYPE_1__ pos; scalar_t__ alen; int /*<<< orphan*/  nvariant; scalar_t__ word; int /*<<< orphan*/  len; } ;
struct TYPE_16__ {int /*<<< orphan*/  prsId; } ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  nvariant; scalar_t__ lexeme; } ;
struct TYPE_14__ {int /*<<< orphan*/  prsend; int /*<<< orphan*/  prstoken; int /*<<< orphan*/  prsstart; } ;
typedef  TYPE_2__ TSParserCacheEntry ;
typedef  TYPE_3__ TSLexeme ;
typedef  TYPE_4__ TSConfigCacheEntry ;
typedef  TYPE_5__ ParsedWord ;
typedef  TYPE_6__ ParsedText ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LexizeData ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  LIMITPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LexizeAddLemm (int /*<<< orphan*/ *,int,char*,int) ; 
 TYPE_3__* LexizeExec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LexizeInit (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int MAXSTRLEN ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  PointerGetDatum (void*) ; 
 int TSL_ADDPOS ; 
 int TSL_PREFIX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_4__* lookup_ts_config_cache (int /*<<< orphan*/ ) ; 
 TYPE_2__* lookup_ts_parser_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 scalar_t__ repalloc (void*,int) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

void
parsetext(Oid cfgId, ParsedText *prs, char *buf, int buflen)
{
	int			type,
				lenlemm;
	char	   *lemm = NULL;
	LexizeData	ldata;
	TSLexeme   *norms;
	TSConfigCacheEntry *cfg;
	TSParserCacheEntry *prsobj;
	void	   *prsdata;

	cfg = lookup_ts_config_cache(cfgId);
	prsobj = lookup_ts_parser_cache(cfg->prsId);

	prsdata = (void *) DatumGetPointer(FunctionCall2(&prsobj->prsstart,
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

		while ((norms = LexizeExec(&ldata, NULL)) != NULL)
		{
			TSLexeme   *ptr = norms;

			prs->pos++;			/* set pos */

			while (ptr->lexeme)
			{
				if (prs->curwords == prs->lenwords)
				{
					prs->lenwords *= 2;
					prs->words = (ParsedWord *) repalloc((void *) prs->words, prs->lenwords * sizeof(ParsedWord));
				}

				if (ptr->flags & TSL_ADDPOS)
					prs->pos++;
				prs->words[prs->curwords].len = strlen(ptr->lexeme);
				prs->words[prs->curwords].word = ptr->lexeme;
				prs->words[prs->curwords].nvariant = ptr->nvariant;
				prs->words[prs->curwords].flags = ptr->flags & TSL_PREFIX;
				prs->words[prs->curwords].alen = 0;
				prs->words[prs->curwords].pos.pos = LIMITPOS(prs->pos);
				ptr++;
				prs->curwords++;
			}
			pfree(norms);
		}
	} while (type > 0);

	FunctionCall1(&(prsobj->prsend), PointerGetDatum(prsdata));
}