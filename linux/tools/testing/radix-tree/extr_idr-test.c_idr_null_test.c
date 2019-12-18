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

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DUMMY_PTR ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  idr ; 
 int idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int idr_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void idr_null_test(void)
{
	int i;
	DEFINE_IDR(idr);

	assert(idr_is_empty(&idr));

	assert(idr_alloc(&idr, NULL, 0, 0, GFP_KERNEL) == 0);
	assert(!idr_is_empty(&idr));
	idr_remove(&idr, 0);
	assert(idr_is_empty(&idr));

	assert(idr_alloc(&idr, NULL, 0, 0, GFP_KERNEL) == 0);
	assert(!idr_is_empty(&idr));
	idr_destroy(&idr);
	assert(idr_is_empty(&idr));

	for (i = 0; i < 10; i++) {
		assert(idr_alloc(&idr, NULL, 0, 0, GFP_KERNEL) == i);
	}

	assert(idr_replace(&idr, DUMMY_PTR, 3) == NULL);
	assert(idr_replace(&idr, DUMMY_PTR, 4) == NULL);
	assert(idr_replace(&idr, NULL, 4) == DUMMY_PTR);
	assert(idr_replace(&idr, DUMMY_PTR, 11) == ERR_PTR(-ENOENT));
	idr_remove(&idr, 5);
	assert(idr_alloc(&idr, NULL, 0, 0, GFP_KERNEL) == 5);
	idr_remove(&idr, 5);

	for (i = 0; i < 9; i++) {
		idr_remove(&idr, i);
		assert(!idr_is_empty(&idr));
	}
	idr_remove(&idr, 8);
	assert(!idr_is_empty(&idr));
	idr_remove(&idr, 9);
	assert(idr_is_empty(&idr));

	assert(idr_alloc(&idr, NULL, 0, 0, GFP_KERNEL) == 0);
	assert(idr_replace(&idr, DUMMY_PTR, 3) == ERR_PTR(-ENOENT));
	assert(idr_replace(&idr, DUMMY_PTR, 0) == NULL);
	assert(idr_replace(&idr, NULL, 0) == DUMMY_PTR);

	idr_destroy(&idr);
	assert(idr_is_empty(&idr));

	for (i = 1; i < 10; i++) {
		assert(idr_alloc(&idr, NULL, 1, 0, GFP_KERNEL) == i);
	}

	idr_destroy(&idr);
	assert(idr_is_empty(&idr));
}