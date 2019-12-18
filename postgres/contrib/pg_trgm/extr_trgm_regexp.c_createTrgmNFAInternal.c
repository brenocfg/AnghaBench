#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  TrgmPackedGraph ;
struct TYPE_10__ {TYPE_1__* initState; int /*<<< orphan*/  ncolors; int /*<<< orphan*/  colorInfo; int /*<<< orphan*/ * regex; } ;
typedef  TYPE_2__ TrgmNFA ;
struct TYPE_9__ {int flags; } ;
typedef  int /*<<< orphan*/  TRGM ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int TSTATE_FIN ; 
 int /*<<< orphan*/ * expandColorTrigrams (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getColorInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * packGraph (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printSourceNFA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printTrgmNFA (TYPE_2__*) ; 
 int /*<<< orphan*/  printTrgmPackedGraph (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selectColorTrigrams (TYPE_2__*) ; 
 int /*<<< orphan*/  transformGraph (TYPE_2__*) ; 

__attribute__((used)) static TRGM *
createTrgmNFAInternal(regex_t *regex, TrgmPackedGraph **graph,
					  MemoryContext rcontext)
{
	TRGM	   *trg;
	TrgmNFA		trgmNFA;

	trgmNFA.regex = regex;

	/* Collect color information from the regex */
	getColorInfo(regex, &trgmNFA);

#ifdef TRGM_REGEXP_DEBUG
	printSourceNFA(regex, trgmNFA.colorInfo, trgmNFA.ncolors);
#endif

	/*
	 * Stage 2: Create an expanded graph from the source NFA.
	 */
	transformGraph(&trgmNFA);

#ifdef TRGM_REGEXP_DEBUG
	printTrgmNFA(&trgmNFA);
#endif

	/*
	 * Fail if we were unable to make a nontrivial graph, ie it is possible to
	 * get from the initial state to the final state without reading any
	 * predictable trigram.
	 */
	if (trgmNFA.initState->flags & TSTATE_FIN)
		return NULL;

	/*
	 * Stage 3: Select color trigrams to expand.  Fail if too many trigrams.
	 */
	if (!selectColorTrigrams(&trgmNFA))
		return NULL;

	/*
	 * Stage 4: Expand color trigrams and pack graph into final
	 * representation.
	 */
	trg = expandColorTrigrams(&trgmNFA, rcontext);

	*graph = packGraph(&trgmNFA, rcontext);

#ifdef TRGM_REGEXP_DEBUG
	printTrgmPackedGraph(*graph, trg);
#endif

	return trg;
}