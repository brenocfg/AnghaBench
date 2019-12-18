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
struct TYPE_3__ {void* typname; void* nspname; int /*<<< orphan*/  remoteid; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ LogicalRepTyp ;

/* Variables and functions */
 int /*<<< orphan*/  logicalrep_read_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_getmsgstring (int /*<<< orphan*/ ) ; 
 void* pstrdup (int /*<<< orphan*/ ) ; 

void
logicalrep_read_typ(StringInfo in, LogicalRepTyp *ltyp)
{
	ltyp->remoteid = pq_getmsgint(in, 4);

	/* Read type name from stream */
	ltyp->nspname = pstrdup(logicalrep_read_namespace(in));
	ltyp->typname = pstrdup(pq_getmsgstring(in));
}