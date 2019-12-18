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
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {int size; TYPE_1__* data; int /*<<< orphan*/  string_length; } ;
struct TYPE_5__ {scalar_t__ worth; } ;
typedef  TYPE_2__ Pool ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ Chromosome ;

/* Variables and functions */
 scalar_t__ DBL_MAX ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ geqo_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tour (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
random_init_pool(PlannerInfo *root, Pool *pool)
{
	Chromosome *chromo = (Chromosome *) pool->data;
	int			i;
	int			bad = 0;

	/*
	 * We immediately discard any invalid individuals (those that geqo_eval
	 * returns DBL_MAX for), thereby not wasting pool space on them.
	 *
	 * If we fail to make any valid individuals after 10000 tries, give up;
	 * this probably means something is broken, and we shouldn't just let
	 * ourselves get stuck in an infinite loop.
	 */
	i = 0;
	while (i < pool->size)
	{
		init_tour(root, chromo[i].string, pool->string_length);
		pool->data[i].worth = geqo_eval(root, chromo[i].string,
										pool->string_length);
		if (pool->data[i].worth < DBL_MAX)
			i++;
		else
		{
			bad++;
			if (i == 0 && bad >= 10000)
				elog(ERROR, "geqo failed to make a valid plan");
		}
	}

#ifdef GEQO_DEBUG
	if (bad > 0)
		elog(DEBUG1, "%d invalid tours found while selecting %d pool entries",
			 bad, pool->size);
#endif
}