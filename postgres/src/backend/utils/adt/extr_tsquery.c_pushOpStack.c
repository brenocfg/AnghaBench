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
typedef  int /*<<< orphan*/  int8 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_3__ {int /*<<< orphan*/  distance; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ OperatorElement ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int STACKDEPTH ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pushOpStack(OperatorElement *stack, int *lenstack, int8 op, int16 distance)
{
	if (*lenstack == STACKDEPTH)	/* internal error */
		elog(ERROR, "tsquery stack too small");

	stack[*lenstack].op = op;
	stack[*lenstack].distance = distance;

	(*lenstack)++;
}