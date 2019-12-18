#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ string; } ;
struct TYPE_4__ {int size; int string_length; TYPE_2__* data; } ;
typedef  TYPE_1__ Pool ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Gene ;
typedef  TYPE_2__ Chromosome ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

Pool *
alloc_pool(PlannerInfo *root, int pool_size, int string_length)
{
	Pool	   *new_pool;
	Chromosome *chromo;
	int			i;

	/* pool */
	new_pool = (Pool *) palloc(sizeof(Pool));
	new_pool->size = (int) pool_size;
	new_pool->string_length = (int) string_length;

	/* all chromosome */
	new_pool->data = (Chromosome *) palloc(pool_size * sizeof(Chromosome));

	/* all gene */
	chromo = (Chromosome *) new_pool->data; /* vector of all chromos */
	for (i = 0; i < pool_size; i++)
		chromo[i].string = palloc((string_length + 1) * sizeof(Gene));

	return new_pool;
}