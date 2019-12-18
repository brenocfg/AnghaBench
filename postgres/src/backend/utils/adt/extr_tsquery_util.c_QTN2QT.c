#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  curoperand; int /*<<< orphan*/  operand; int /*<<< orphan*/  curitem; } ;
struct TYPE_8__ {int size; } ;
typedef  TYPE_1__* TSQuery ;
typedef  int /*<<< orphan*/  QTNode ;
typedef  TYPE_2__ QTN2QTState ;

/* Variables and functions */
 int COMPUTESIZE (int,int) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETOPERAND (TYPE_1__*) ; 
 int /*<<< orphan*/  GETQUERY (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int) ; 
 scalar_t__ TSQUERY_TOO_BIG (int,int) ; 
 int /*<<< orphan*/  cntsize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  fillQT (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 

TSQuery
QTN2QT(QTNode *in)
{
	TSQuery		out;
	int			len;
	int			sumlen = 0,
				nnode = 0;
	QTN2QTState state;

	cntsize(in, &sumlen, &nnode);

	if (TSQUERY_TOO_BIG(nnode, sumlen))
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("tsquery is too large")));
	len = COMPUTESIZE(nnode, sumlen);

	out = (TSQuery) palloc0(len);
	SET_VARSIZE(out, len);
	out->size = nnode;

	state.curitem = GETQUERY(out);
	state.operand = state.curoperand = GETOPERAND(out);

	fillQT(&state, in);
	return out;
}