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

/* Variables and functions */
 int /*<<< orphan*/  DefineCustomRealVariable (char*,char*,char*,int /*<<< orphan*/ *,double,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGC_USERSET ; 
 int /*<<< orphan*/  similarity_threshold ; 
 int /*<<< orphan*/  strict_word_similarity_threshold ; 
 int /*<<< orphan*/  word_similarity_threshold ; 

void
_PG_init(void)
{
	/* Define custom GUC variables. */
	DefineCustomRealVariable("pg_trgm.similarity_threshold",
							 "Sets the threshold used by the % operator.",
							 "Valid range is 0.0 .. 1.0.",
							 &similarity_threshold,
							 0.3,
							 0.0,
							 1.0,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);
	DefineCustomRealVariable("pg_trgm.word_similarity_threshold",
							 "Sets the threshold used by the <% operator.",
							 "Valid range is 0.0 .. 1.0.",
							 &word_similarity_threshold,
							 0.6,
							 0.0,
							 1.0,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);
	DefineCustomRealVariable("pg_trgm.strict_word_similarity_threshold",
							 "Sets the threshold used by the <<% operator.",
							 "Valid range is 0.0 .. 1.0.",
							 &strict_word_similarity_threshold,
							 0.5,
							 0.0,
							 1.0,
							 PGC_USERSET,
							 0,
							 NULL,
							 NULL,
							 NULL);
}