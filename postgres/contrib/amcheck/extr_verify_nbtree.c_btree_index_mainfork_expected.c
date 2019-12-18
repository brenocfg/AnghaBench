#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* rd_rel; } ;
struct TYPE_5__ {scalar_t__ relpersistence; } ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_READ_ONLY_SQL_TRANSACTION ; 
 int /*<<< orphan*/  NOTICE ; 
 scalar_t__ RELPERSISTENCE_UNLOGGED ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
btree_index_mainfork_expected(Relation rel)
{
	if (rel->rd_rel->relpersistence != RELPERSISTENCE_UNLOGGED ||
		!RecoveryInProgress())
		return true;

	ereport(NOTICE,
			(errcode(ERRCODE_READ_ONLY_SQL_TRANSACTION),
			 errmsg("cannot verify unlogged index \"%s\" during recovery, skipping",
					RelationGetRelationName(rel))));

	return false;
}