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
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  polstr; } ;
typedef  TYPE_1__* TSQueryParserState ;
typedef  TYPE_2__ QueryOperand ;

/* Variables and functions */
 int /*<<< orphan*/  QI_VALSTOP ; 
 int /*<<< orphan*/  lcons (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 

void
pushStop(TSQueryParserState state)
{
	QueryOperand *tmp;

	tmp = (QueryOperand *) palloc0(sizeof(QueryOperand));
	tmp->type = QI_VALSTOP;

	state->polstr = lcons(tmp, state->polstr);
}