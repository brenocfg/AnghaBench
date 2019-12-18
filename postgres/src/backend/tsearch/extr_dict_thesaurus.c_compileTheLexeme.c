#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {struct TYPE_22__* lexeme; struct TYPE_22__* entries; struct TYPE_22__* nextentry; scalar_t__ idsubst; } ;
typedef  TYPE_2__ TheLexeme ;
struct TYPE_24__ {int nwrds; int ntwrds; TYPE_2__* wrds; TYPE_1__* subdict; } ;
struct TYPE_23__ {int nvariant; scalar_t__ lexeme; } ;
struct TYPE_21__ {TYPE_2__* dictData; int /*<<< orphan*/  lexize; } ;
typedef  TYPE_3__ TSLexeme ;
typedef  TYPE_4__ DictThesaurus ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_2__*) ; 
 TYPE_2__* addCompiledLexeme (TYPE_2__*,int*,int*,TYPE_3__*,TYPE_2__*,int) ; 
 scalar_t__ cmpLexeme (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ cmpLexemeInfo (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  cmpTheLexeme ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,TYPE_2__*,scalar_t__) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 int /*<<< orphan*/  qsort (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (TYPE_2__*,int) ; 
 scalar_t__ strcmp (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  strlen (TYPE_2__*) ; 

__attribute__((used)) static void
compileTheLexeme(DictThesaurus *d)
{
	int			i,
				nnw = 0,
				tnm = 16;
	TheLexeme  *newwrds = (TheLexeme *) palloc(sizeof(TheLexeme) * tnm),
			   *ptrwrds;

	for (i = 0; i < d->nwrds; i++)
	{
		TSLexeme   *ptr;

		if (strcmp(d->wrds[i].lexeme, "?") == 0)	/* Is stop word marker? */
			newwrds = addCompiledLexeme(newwrds, &nnw, &tnm, NULL, d->wrds[i].entries, 0);
		else
		{
			ptr = (TSLexeme *) DatumGetPointer(FunctionCall4(&(d->subdict->lexize),
															 PointerGetDatum(d->subdict->dictData),
															 PointerGetDatum(d->wrds[i].lexeme),
															 Int32GetDatum(strlen(d->wrds[i].lexeme)),
															 PointerGetDatum(NULL)));

			if (!ptr)
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("thesaurus sample word \"%s\" isn't recognized by subdictionary (rule %d)",
								d->wrds[i].lexeme,
								d->wrds[i].entries->idsubst + 1)));
			else if (!(ptr->lexeme))
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("thesaurus sample word \"%s\" is a stop word (rule %d)",
								d->wrds[i].lexeme,
								d->wrds[i].entries->idsubst + 1),
						 errhint("Use \"?\" to represent a stop word within a sample phrase.")));
			else
			{
				while (ptr->lexeme)
				{
					TSLexeme   *remptr = ptr + 1;
					int			tnvar = 1;
					int			curvar = ptr->nvariant;

					/* compute n words in one variant */
					while (remptr->lexeme)
					{
						if (remptr->nvariant != (remptr - 1)->nvariant)
							break;
						tnvar++;
						remptr++;
					}

					remptr = ptr;
					while (remptr->lexeme && remptr->nvariant == curvar)
					{
						newwrds = addCompiledLexeme(newwrds, &nnw, &tnm, remptr, d->wrds[i].entries, tnvar);
						remptr++;
					}

					ptr = remptr;
				}
			}
		}

		pfree(d->wrds[i].lexeme);
		pfree(d->wrds[i].entries);
	}

	if (d->wrds)
		pfree(d->wrds);
	d->wrds = newwrds;
	d->nwrds = nnw;
	d->ntwrds = tnm;

	if (d->nwrds > 1)
	{
		qsort(d->wrds, d->nwrds, sizeof(TheLexeme), cmpTheLexeme);

		/* uniq */
		newwrds = d->wrds;
		ptrwrds = d->wrds + 1;
		while (ptrwrds - d->wrds < d->nwrds)
		{
			if (cmpLexeme(ptrwrds, newwrds) == 0)
			{
				if (cmpLexemeInfo(ptrwrds->entries, newwrds->entries))
				{
					ptrwrds->entries->nextentry = newwrds->entries;
					newwrds->entries = ptrwrds->entries;
				}
				else
					pfree(ptrwrds->entries);

				if (ptrwrds->lexeme)
					pfree(ptrwrds->lexeme);
			}
			else
			{
				newwrds++;
				*newwrds = *ptrwrds;
			}

			ptrwrds++;
		}

		d->nwrds = newwrds - d->wrds + 1;
		d->wrds = (TheLexeme *) repalloc(d->wrds, sizeof(TheLexeme) * d->nwrds);
	}
}