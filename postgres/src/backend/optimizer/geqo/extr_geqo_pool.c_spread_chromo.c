#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ worth; int /*<<< orphan*/  string; } ;
struct TYPE_8__ {scalar_t__ worth; int /*<<< orphan*/  string; } ;
struct TYPE_7__ {int size; TYPE_5__* data; int /*<<< orphan*/  string_length; } ;
typedef  TYPE_1__ Pool ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ Chromosome ;

/* Variables and functions */
 int /*<<< orphan*/  geqo_copy (int /*<<< orphan*/ *,TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

void
spread_chromo(PlannerInfo *root, Chromosome *chromo, Pool *pool)
{
	int			top,
				mid,
				bot;
	int			i,
				index;
	Chromosome	swap_chromo,
				tmp_chromo;

	/* new chromo is so bad we can't use it */
	if (chromo->worth > pool->data[pool->size - 1].worth)
		return;

	/* do a binary search to find the index of the new chromo */

	top = 0;
	mid = pool->size / 2;
	bot = pool->size - 1;
	index = -1;

	while (index == -1)
	{
		/* these 4 cases find a new location */

		if (chromo->worth <= pool->data[top].worth)
			index = top;
		else if (chromo->worth == pool->data[mid].worth)
			index = mid;
		else if (chromo->worth == pool->data[bot].worth)
			index = bot;
		else if (bot - top <= 1)
			index = bot;


		/*
		 * these 2 cases move the search indices since a new location has not
		 * yet been found.
		 */

		else if (chromo->worth < pool->data[mid].worth)
		{
			bot = mid;
			mid = top + ((bot - top) / 2);
		}
		else
		{						/* (chromo->worth > pool->data[mid].worth) */
			top = mid;
			mid = top + ((bot - top) / 2);
		}
	}							/* ... while */

	/* now we have index for chromo */

	/*
	 * move every gene from index on down one position to make room for chromo
	 */

	/*
	 * copy new gene into pool storage; always replace worst gene in pool
	 */

	geqo_copy(root, &pool->data[pool->size - 1], chromo, pool->string_length);

	swap_chromo.string = pool->data[pool->size - 1].string;
	swap_chromo.worth = pool->data[pool->size - 1].worth;

	for (i = index; i < pool->size; i++)
	{
		tmp_chromo.string = pool->data[i].string;
		tmp_chromo.worth = pool->data[i].worth;

		pool->data[i].string = swap_chromo.string;
		pool->data[i].worth = swap_chromo.worth;

		swap_chromo.string = tmp_chromo.string;
		swap_chromo.worth = tmp_chromo.worth;
	}
}