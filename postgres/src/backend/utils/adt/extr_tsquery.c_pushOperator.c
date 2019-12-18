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
typedef  scalar_t__ int8 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_6__ {int /*<<< orphan*/  distance; scalar_t__ oper; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  polstr; } ;
typedef  TYPE_1__* TSQueryParserState ;
typedef  TYPE_2__ QueryOperator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ OP_AND ; 
 scalar_t__ OP_NOT ; 
 scalar_t__ OP_OR ; 
 scalar_t__ OP_PHRASE ; 
 int /*<<< orphan*/  QI_OPR ; 
 int /*<<< orphan*/  lcons (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 

void
pushOperator(TSQueryParserState state, int8 oper, int16 distance)
{
	QueryOperator *tmp;

	Assert(oper == OP_NOT || oper == OP_AND || oper == OP_OR || oper == OP_PHRASE);

	tmp = (QueryOperator *) palloc0(sizeof(QueryOperator));
	tmp->type = QI_OPR;
	tmp->oper = oper;
	tmp->distance = (oper == OP_PHRASE) ? distance : 0;
	/* left is filled in later with findoprnd */

	state->polstr = lcons(tmp, state->polstr);
}