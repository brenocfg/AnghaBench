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
struct item {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IDR (int /*<<< orphan*/ ) ; 
 struct item* DUMMY_PTR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  idr ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct item*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 struct item* item_create (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_idr_free ; 

void idr_alloc_test(void)
{
	unsigned long i;
	DEFINE_IDR(idr);

	assert(idr_alloc_cyclic(&idr, DUMMY_PTR, 0, 0x4000, GFP_KERNEL) == 0);
	assert(idr_alloc_cyclic(&idr, DUMMY_PTR, 0x3ffd, 0x4000, GFP_KERNEL) == 0x3ffd);
	idr_remove(&idr, 0x3ffd);
	idr_remove(&idr, 0);

	for (i = 0x3ffe; i < 0x4003; i++) {
		int id;
		struct item *item;

		if (i < 0x4000)
			item = item_create(i, 0);
		else
			item = item_create(i - 0x3fff, 0);

		id = idr_alloc_cyclic(&idr, item, 1, 0x4000, GFP_KERNEL);
		assert(id == item->index);
	}

	idr_for_each(&idr, item_idr_free, &idr);
	idr_destroy(&idr);
}