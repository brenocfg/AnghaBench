#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ecpgQuery; scalar_t__* stmtID; } ;

/* Variables and functions */
 int HashStmt (char const*) ; 
 int stmtCacheEntPerBucket ; 
 TYPE_1__* stmtCacheEntries ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
SearchStmtCache(const char *ecpgQuery)
{
	int			entNo,
				entIx;

	/* quick failure if cache not set up */
	if (stmtCacheEntries == NULL)
		return 0;

	/* hash the statement */
	entNo = HashStmt(ecpgQuery);

	/* search the cache */
	for (entIx = 0; entIx < stmtCacheEntPerBucket; ++entIx)
	{
		if (stmtCacheEntries[entNo].stmtID[0])	/* check if entry is in use */
		{
			if (strcmp(ecpgQuery, stmtCacheEntries[entNo].ecpgQuery) == 0)
				break;			/* found it */
		}
		++entNo;				/* incr entry # */
	}

	/* if entry wasn't found - set entry # to zero */
	if (entIx >= stmtCacheEntPerBucket)
		entNo = 0;

	return entNo;
}