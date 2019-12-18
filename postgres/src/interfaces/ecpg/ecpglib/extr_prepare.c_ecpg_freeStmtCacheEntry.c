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
struct prepared_statement {int dummy; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {char* stmtID; scalar_t__ ecpgQuery; int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ stmtCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  deallocate_one (int,int,struct connection*,struct prepared_statement*,struct prepared_statement*) ; 
 struct prepared_statement* ecpg_find_prepared_statement (char*,struct connection*,struct prepared_statement**) ; 
 int /*<<< orphan*/  ecpg_free (scalar_t__) ; 
 struct connection* ecpg_get_connection (int /*<<< orphan*/ ) ; 
 TYPE_1__* stmtCacheEntries ; 

__attribute__((used)) static int
ecpg_freeStmtCacheEntry(int lineno, int compat,
						int entNo)	/* entry # to free */
{
	stmtCacheEntry *entry;
	struct connection *con;
	struct prepared_statement *this,
			   *prev;

	/* fail if cache isn't set up */
	if (stmtCacheEntries == NULL)
		return -1;

	entry = &stmtCacheEntries[entNo];
	if (!entry->stmtID[0])		/* return if the entry isn't in use */
		return 0;

	con = ecpg_get_connection(entry->connection);

	/* free the 'prepared_statement' list entry */
	this = ecpg_find_prepared_statement(entry->stmtID, con, &prev);
	if (this && !deallocate_one(lineno, compat, con, prev, this))
		return -1;

	entry->stmtID[0] = '\0';

	/* free the memory used by the cache entry */
	if (entry->ecpgQuery)
	{
		ecpg_free(entry->ecpgQuery);
		entry->ecpgQuery = 0;
	}

	return entNo;
}