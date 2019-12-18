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
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  idr ; 
 unsigned int idr_alloc (int /*<<< orphan*/ *,struct item*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 struct item* item_create (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_idr_free ; 

void idr_nowait_test(void)
{
	unsigned int i;
	DEFINE_IDR(idr);

	idr_preload(GFP_KERNEL);

	for (i = 0; i < 3; i++) {
		struct item *item = item_create(i, 0);
		assert(idr_alloc(&idr, item, i, i + 1, GFP_NOWAIT) == i);
	}

	idr_preload_end();

	idr_for_each(&idr, item_idr_free, &idr);
	idr_destroy(&idr);
}