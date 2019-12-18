#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_6__ {char* lexeme; struct TYPE_6__* res; scalar_t__ flags; scalar_t__ nvariant; scalar_t__ lastlexeme; } ;
typedef  TYPE_1__ TheSubstitute ;
struct TYPE_7__ {int nsubst; TYPE_1__* subst; } ;
typedef  TYPE_1__ TSLexeme ;
typedef  TYPE_3__ DictThesaurus ;

/* Variables and functions */
 scalar_t__ DT_USEASIS ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* palloc (int) ; 
 scalar_t__ repalloc (TYPE_1__*,int) ; 

__attribute__((used)) static void
addWrd(DictThesaurus *d, char *b, char *e, uint32 idsubst, uint16 nwrd, uint16 posinsubst, bool useasis)
{
	static int	nres = 0;
	static int	ntres = 0;
	TheSubstitute *ptr;

	if (nwrd == 0)
	{
		nres = ntres = 0;

		if (idsubst >= d->nsubst)
		{
			if (d->nsubst == 0)
			{
				d->nsubst = 16;
				d->subst = (TheSubstitute *) palloc(sizeof(TheSubstitute) * d->nsubst);
			}
			else
			{
				d->nsubst *= 2;
				d->subst = (TheSubstitute *) repalloc(d->subst, sizeof(TheSubstitute) * d->nsubst);
			}
		}
	}

	ptr = d->subst + idsubst;

	ptr->lastlexeme = posinsubst - 1;

	if (nres + 1 >= ntres)
	{
		if (ntres == 0)
		{
			ntres = 2;
			ptr->res = (TSLexeme *) palloc(sizeof(TSLexeme) * ntres);
		}
		else
		{
			ntres *= 2;
			ptr->res = (TSLexeme *) repalloc(ptr->res, sizeof(TSLexeme) * ntres);
		}
	}

	ptr->res[nres].lexeme = palloc(e - b + 1);
	memcpy(ptr->res[nres].lexeme, b, e - b);
	ptr->res[nres].lexeme[e - b] = '\0';

	ptr->res[nres].nvariant = nwrd;
	if (useasis)
		ptr->res[nres].flags = DT_USEASIS;
	else
		ptr->res[nres].flags = 0;

	ptr->res[++nres].lexeme = NULL;
}