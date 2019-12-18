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
struct TYPE_11__ {scalar_t__ type; int flagflags; scalar_t__ replen; int /*<<< orphan*/ * repl; int /*<<< orphan*/  flag; } ;
struct TYPE_10__ {int issuffix; scalar_t__ len; int /*<<< orphan*/ * affix; } ;
struct TYPE_9__ {int naffixes; void* Suffix; void* Prefix; TYPE_2__* CompoundAffix; scalar_t__ Affix; } ;
typedef  TYPE_1__ IspellDict ;
typedef  TYPE_2__ CMPDAffix ;
typedef  TYPE_3__ AFFIX ;

/* Variables and functions */
 int FF_COMPOUNDFLAG ; 
 scalar_t__ FF_PREFIX ; 
 scalar_t__ FF_SUFFIX ; 
 int /*<<< orphan*/  cmpaffix ; 
 scalar_t__ isAffixInUse (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* mkANode (TYPE_1__*,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mkVoidAffix (TYPE_1__*,int,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (TYPE_2__*,int) ; 
 scalar_t__ strbncmp (unsigned char const*,unsigned char const*,scalar_t__) ; 

void
NISortAffixes(IspellDict *Conf)
{
	AFFIX	   *Affix;
	size_t		i;
	CMPDAffix  *ptr;
	int			firstsuffix = Conf->naffixes;

	if (Conf->naffixes == 0)
		return;

	/* Store compound affixes in the Conf->CompoundAffix array */
	if (Conf->naffixes > 1)
		qsort((void *) Conf->Affix, Conf->naffixes, sizeof(AFFIX), cmpaffix);
	Conf->CompoundAffix = ptr = (CMPDAffix *) palloc(sizeof(CMPDAffix) * Conf->naffixes);
	ptr->affix = NULL;

	for (i = 0; i < Conf->naffixes; i++)
	{
		Affix = &(((AFFIX *) Conf->Affix)[i]);
		if (Affix->type == FF_SUFFIX && i < firstsuffix)
			firstsuffix = i;

		if ((Affix->flagflags & FF_COMPOUNDFLAG) && Affix->replen > 0 &&
			isAffixInUse(Conf, Affix->flag))
		{
			bool		issuffix = (Affix->type == FF_SUFFIX);

			if (ptr == Conf->CompoundAffix ||
				issuffix != (ptr - 1)->issuffix ||
				strbncmp((const unsigned char *) (ptr - 1)->affix,
						 (const unsigned char *) Affix->repl,
						 (ptr - 1)->len))
			{
				/* leave only unique and minimals suffixes */
				ptr->affix = Affix->repl;
				ptr->len = Affix->replen;
				ptr->issuffix = issuffix;
				ptr++;
			}
		}
	}
	ptr->affix = NULL;
	Conf->CompoundAffix = (CMPDAffix *) repalloc(Conf->CompoundAffix, sizeof(CMPDAffix) * (ptr - Conf->CompoundAffix + 1));

	/* Start build a prefix tree */
	Conf->Prefix = mkANode(Conf, 0, firstsuffix, 0, FF_PREFIX);
	Conf->Suffix = mkANode(Conf, firstsuffix, Conf->naffixes, 0, FF_SUFFIX);
	mkVoidAffix(Conf, true, firstsuffix);
	mkVoidAffix(Conf, false, firstsuffix);
}