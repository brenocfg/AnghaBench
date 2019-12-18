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
struct TYPE_6__ {TYPE_1__* string; } ;
struct TYPE_5__ {int size; struct TYPE_5__* data; } ;
typedef  TYPE_1__ Pool ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ Chromosome ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
free_pool(PlannerInfo *root, Pool *pool)
{
	Chromosome *chromo;
	int			i;

	/* all gene */
	chromo = (Chromosome *) pool->data; /* vector of all chromos */
	for (i = 0; i < pool->size; i++)
		pfree(chromo[i].string);

	/* all chromosome */
	pfree(pool->data);

	/* pool */
	pfree(pool);
}