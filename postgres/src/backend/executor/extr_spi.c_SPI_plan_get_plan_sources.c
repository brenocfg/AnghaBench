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
struct TYPE_3__ {scalar_t__ magic; int /*<<< orphan*/ * plancache_list; } ;
typedef  TYPE_1__* SPIPlanPtr ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ _SPI_PLAN_MAGIC ; 

List *
SPI_plan_get_plan_sources(SPIPlanPtr plan)
{
	Assert(plan->magic == _SPI_PLAN_MAGIC);
	return plan->plancache_list;
}