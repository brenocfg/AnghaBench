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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  LogicalRepTupleData ;
typedef  int /*<<< orphan*/  LogicalRepRelId ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  logicalrep_read_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgint (int /*<<< orphan*/ ,int) ; 

LogicalRepRelId
logicalrep_read_update(StringInfo in, bool *has_oldtuple,
					   LogicalRepTupleData *oldtup,
					   LogicalRepTupleData *newtup)
{
	char		action;
	LogicalRepRelId relid;

	/* read the relation id */
	relid = pq_getmsgint(in, 4);

	/* read and verify action */
	action = pq_getmsgbyte(in);
	if (action != 'K' && action != 'O' && action != 'N')
		elog(ERROR, "expected action 'N', 'O' or 'K', got %c",
			 action);

	/* check for old tuple */
	if (action == 'K' || action == 'O')
	{
		logicalrep_read_tuple(in, oldtup);
		*has_oldtuple = true;

		action = pq_getmsgbyte(in);
	}
	else
		*has_oldtuple = false;

	/* check for new  tuple */
	if (action != 'N')
		elog(ERROR, "expected action 'N', got %c",
			 action);

	logicalrep_read_tuple(in, newtup);

	return relid;
}