#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ qual; scalar_t__ targetlist; } ;
struct TYPE_11__ {TYPE_3__ plan; } ;
struct TYPE_7__ {scalar_t__ plan; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;
struct TYPE_10__ {TYPE_2__ ss; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  TYPE_4__ AggState ;
typedef  TYPE_5__ Agg ;

/* Variables and functions */
 int /*<<< orphan*/  find_unaggregated_cols_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static Bitmapset *
find_unaggregated_cols(AggState *aggstate)
{
	Agg		   *node = (Agg *) aggstate->ss.ps.plan;
	Bitmapset  *colnos;

	colnos = NULL;
	(void) find_unaggregated_cols_walker((Node *) node->plan.targetlist,
										 &colnos);
	(void) find_unaggregated_cols_walker((Node *) node->plan.qual,
										 &colnos);
	return colnos;
}