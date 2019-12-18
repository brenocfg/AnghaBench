#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * bms_add_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_del_member (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bms_del_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_make_singleton (int) ; 
 void* palloc (int) ; 

Bitmapset *
DiscreteKnapsack(int max_weight, int num_items,
				 int *item_weights, double *item_values)
{
	MemoryContext local_ctx = AllocSetContextCreate(CurrentMemoryContext,
													"Knapsack",
													ALLOCSET_SMALL_SIZES);
	MemoryContext oldctx = MemoryContextSwitchTo(local_ctx);
	double	   *values;
	Bitmapset **sets;
	Bitmapset  *result;
	int			i,
				j;

	Assert(max_weight >= 0);
	Assert(num_items > 0 && item_weights);

	values = palloc((1 + max_weight) * sizeof(double));
	sets = palloc((1 + max_weight) * sizeof(Bitmapset *));

	for (i = 0; i <= max_weight; ++i)
	{
		values[i] = 0;
		sets[i] = bms_make_singleton(num_items);
	}

	for (i = 0; i < num_items; ++i)
	{
		int			iw = item_weights[i];
		double		iv = item_values ? item_values[i] : 1;

		for (j = max_weight; j >= iw; --j)
		{
			int			ow = j - iw;

			if (values[j] <= values[ow] + iv)
			{
				/* copy sets[ow] to sets[j] without realloc */
				if (j != ow)
				{
					sets[j] = bms_del_members(sets[j], sets[j]);
					sets[j] = bms_add_members(sets[j], sets[ow]);
				}

				sets[j] = bms_add_member(sets[j], i);

				values[j] = values[ow] + iv;
			}
		}
	}

	MemoryContextSwitchTo(oldctx);

	result = bms_del_member(bms_copy(sets[max_weight]), num_items);

	MemoryContextDelete(local_ctx);

	return result;
}