#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  scalar_t__ int8 ;
struct TYPE_7__ {int nchild; struct TYPE_7__** child; TYPE_2__* valnode; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  distance; scalar_t__ oper; } ;
struct TYPE_6__ {TYPE_1__ qoperator; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  TSQuery ;
typedef  TYPE_2__ QueryItem ;
typedef  TYPE_3__ QTNode ;

/* Variables and functions */
 int /*<<< orphan*/  GETOPERAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETQUERY (int /*<<< orphan*/ ) ; 
 scalar_t__ OP_PHRASE ; 
 int /*<<< orphan*/  QI_OPR ; 
 void* QT2QTN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QTN_NEEDFREE ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static QTNode *
join_tsqueries(TSQuery a, TSQuery b, int8 operator, uint16 distance)
{
	QTNode	   *res = (QTNode *) palloc0(sizeof(QTNode));

	res->flags |= QTN_NEEDFREE;

	res->valnode = (QueryItem *) palloc0(sizeof(QueryItem));
	res->valnode->type = QI_OPR;
	res->valnode->qoperator.oper = operator;
	if (operator == OP_PHRASE)
		res->valnode->qoperator.distance = distance;

	res->child = (QTNode **) palloc0(sizeof(QTNode *) * 2);
	res->child[0] = QT2QTN(GETQUERY(b), GETOPERAND(b));
	res->child[1] = QT2QTN(GETQUERY(a), GETOPERAND(a));
	res->nchild = 2;

	return res;
}