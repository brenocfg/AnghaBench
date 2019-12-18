#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nsubst; TYPE_2__* subst; TYPE_1__* subdict; } ;
struct TYPE_14__ {int flags; struct TYPE_14__* lexeme; } ;
struct TYPE_13__ {int reslen; TYPE_3__* res; } ;
struct TYPE_12__ {TYPE_3__* dictData; int /*<<< orphan*/  lexize; } ;
typedef  TYPE_3__ TSLexeme ;
typedef  TYPE_4__ DictThesaurus ;

/* Variables and functions */
 int DT_USEASIS ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_3__*) ; 
 int TSL_ADDPOS ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 TYPE_3__* pstrdup (TYPE_3__*) ; 
 scalar_t__ repalloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  strlen (TYPE_3__*) ; 

__attribute__((used)) static void
compileTheSubstitute(DictThesaurus *d)
{
	int			i;

	for (i = 0; i < d->nsubst; i++)
	{
		TSLexeme   *rem = d->subst[i].res,
				   *outptr,
				   *inptr;
		int			n = 2;

		outptr = d->subst[i].res = (TSLexeme *) palloc(sizeof(TSLexeme) * n);
		outptr->lexeme = NULL;
		inptr = rem;

		while (inptr && inptr->lexeme)
		{
			TSLexeme   *lexized,
						tmplex[2];

			if (inptr->flags & DT_USEASIS)
			{					/* do not lexize */
				tmplex[0] = *inptr;
				tmplex[0].flags = 0;
				tmplex[1].lexeme = NULL;
				lexized = tmplex;
			}
			else
			{
				lexized = (TSLexeme *) DatumGetPointer(
													   FunctionCall4(
																	 &(d->subdict->lexize),
																	 PointerGetDatum(d->subdict->dictData),
																	 PointerGetDatum(inptr->lexeme),
																	 Int32GetDatum(strlen(inptr->lexeme)),
																	 PointerGetDatum(NULL)
																	 )
					);
			}

			if (lexized && lexized->lexeme)
			{
				int			toset = (lexized->lexeme && outptr != d->subst[i].res) ? (outptr - d->subst[i].res) : -1;

				while (lexized->lexeme)
				{
					if (outptr - d->subst[i].res + 1 >= n)
					{
						int			diff = outptr - d->subst[i].res;

						n *= 2;
						d->subst[i].res = (TSLexeme *) repalloc(d->subst[i].res, sizeof(TSLexeme) * n);
						outptr = d->subst[i].res + diff;
					}

					*outptr = *lexized;
					outptr->lexeme = pstrdup(lexized->lexeme);

					outptr++;
					lexized++;
				}

				if (toset > 0)
					d->subst[i].res[toset].flags |= TSL_ADDPOS;
			}
			else if (lexized)
			{
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("thesaurus substitute word \"%s\" is a stop word (rule %d)",
								inptr->lexeme, i + 1)));
			}
			else
			{
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("thesaurus substitute word \"%s\" isn't recognized by subdictionary (rule %d)",
								inptr->lexeme, i + 1)));
			}

			if (inptr->lexeme)
				pfree(inptr->lexeme);
			inptr++;
		}

		if (outptr == d->subst[i].res)
			ereport(ERROR,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("thesaurus substitute phrase is empty (rule %d)",
							i + 1)));

		d->subst[i].reslen = outptr - d->subst[i].res;

		pfree(rem);
	}
}