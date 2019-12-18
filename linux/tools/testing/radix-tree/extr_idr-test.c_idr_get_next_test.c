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
struct item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  idr ; 
 int idr_alloc (int /*<<< orphan*/ *,struct item*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_get_next (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int) ; 
 struct item* item_create (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_idr_free ; 

void idr_get_next_test(int base)
{
	unsigned long i;
	int nextid;
	DEFINE_IDR(idr);
	idr_init_base(&idr, base);

	int indices[] = {4, 7, 9, 15, 65, 128, 1000, 99999, 0};

	for(i = 0; indices[i]; i++) {
		struct item *item = item_create(indices[i], 0);
		assert(idr_alloc(&idr, item, indices[i], indices[i+1],
				 GFP_KERNEL) == indices[i]);
	}

	for(i = 0, nextid = 0; indices[i]; i++) {
		idr_get_next(&idr, &nextid);
		assert(nextid == indices[i]);
		nextid++;
	}

	idr_for_each(&idr, item_idr_free, &idr);
	idr_destroy(&idr);
}