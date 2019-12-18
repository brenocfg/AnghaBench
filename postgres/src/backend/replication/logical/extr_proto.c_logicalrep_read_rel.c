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
struct TYPE_5__ {int /*<<< orphan*/  replident; void* relname; void* nspname; int /*<<< orphan*/  remoteid; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ LogicalRepRelation ;

/* Variables and functions */
 int /*<<< orphan*/  logicalrep_read_attrs (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  logicalrep_read_namespace (int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_getmsgstring (int /*<<< orphan*/ ) ; 
 void* pstrdup (int /*<<< orphan*/ ) ; 

LogicalRepRelation *
logicalrep_read_rel(StringInfo in)
{
	LogicalRepRelation *rel = palloc(sizeof(LogicalRepRelation));

	rel->remoteid = pq_getmsgint(in, 4);

	/* Read relation name from stream */
	rel->nspname = pstrdup(logicalrep_read_namespace(in));
	rel->relname = pstrdup(pq_getmsgstring(in));

	/* Read the replica identity. */
	rel->replident = pq_getmsgbyte(in);

	/* Get attribute description */
	logicalrep_read_attrs(in, rel);

	return rel;
}