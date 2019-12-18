#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tables; } ;
typedef  int /*<<< orphan*/  PgStat_StatTabEntry ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ PointerIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PgStat_StatTabEntry *
get_pgstat_tabentry_relid(Oid relid, bool isshared, PgStat_StatDBEntry *shared,
						  PgStat_StatDBEntry *dbentry)
{
	PgStat_StatTabEntry *tabentry = NULL;

	if (isshared)
	{
		if (PointerIsValid(shared))
			tabentry = hash_search(shared->tables, &relid,
								   HASH_FIND, NULL);
	}
	else if (PointerIsValid(dbentry))
		tabentry = hash_search(dbentry->tables, &relid,
							   HASH_FIND, NULL);

	return tabentry;
}