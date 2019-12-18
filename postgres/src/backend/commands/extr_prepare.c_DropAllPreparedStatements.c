#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stmt_name; int /*<<< orphan*/  plansource; } ;
typedef  TYPE_1__ PreparedStatement ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DropCachedPlan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepared_queries ; 

void
DropAllPreparedStatements(void)
{
	HASH_SEQ_STATUS seq;
	PreparedStatement *entry;

	/* nothing cached */
	if (!prepared_queries)
		return;

	/* walk over cache */
	hash_seq_init(&seq, prepared_queries);
	while ((entry = hash_seq_search(&seq)) != NULL)
	{
		/* Release the plancache entry */
		DropCachedPlan(entry->plansource);

		/* Now we can remove the hash table entry */
		hash_search(prepared_queries, entry->stmt_name, HASH_REMOVE, NULL);
	}
}