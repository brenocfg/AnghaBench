#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  TrgmPackedGraph ;
typedef  int /*<<< orphan*/  TRGM ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int REG_ADVANCED ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  RE_compile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * createTrgmNFAInternal (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_regfree (int /*<<< orphan*/ *) ; 

TRGM *
createTrgmNFA(text *text_re, Oid collation,
			  TrgmPackedGraph **graph, MemoryContext rcontext)
{
	TRGM	   *trg;
	regex_t		regex;
	MemoryContext tmpcontext;
	MemoryContext oldcontext;

	/*
	 * This processing generates a great deal of cruft, which we'd like to
	 * clean up before returning (since this function may be called in a
	 * query-lifespan memory context).  Make a temp context we can work in so
	 * that cleanup is easy.
	 */
	tmpcontext = AllocSetContextCreate(CurrentMemoryContext,
									   "createTrgmNFA temporary context",
									   ALLOCSET_DEFAULT_SIZES);
	oldcontext = MemoryContextSwitchTo(tmpcontext);

	/*
	 * Stage 1: Compile the regexp into a NFA, using the regexp library.
	 */
#ifdef IGNORECASE
	RE_compile(&regex, text_re, REG_ADVANCED | REG_ICASE, collation);
#else
	RE_compile(&regex, text_re, REG_ADVANCED, collation);
#endif

	/*
	 * Since the regexp library allocates its internal data structures with
	 * malloc, we need to use a PG_TRY block to ensure that pg_regfree() gets
	 * done even if there's an error.
	 */
	PG_TRY();
	{
		trg = createTrgmNFAInternal(&regex, graph, rcontext);
	}
	PG_FINALLY();
	{
		pg_regfree(&regex);
	}
	PG_END_TRY();

	/* Clean up all the cruft we created */
	MemoryContextSwitchTo(oldcontext);
	MemoryContextDelete(tmpcontext);

	return trg;
}