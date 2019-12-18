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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  find_idr ; 
 int idr_alloc (int /*<<< orphan*/ *,void*,int,int,int /*<<< orphan*/ ) ; 
 void* idr_get_next (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  idr_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_throbber ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 void* xa_mk_value (int) ; 

void idr_find_test_1(int anchor_id, int throbber_id)
{
	pthread_t throbber;
	time_t start = time(NULL);

	pthread_create(&throbber, NULL, idr_throbber, &throbber_id);

	BUG_ON(idr_alloc(&find_idr, xa_mk_value(anchor_id), anchor_id,
				anchor_id + 1, GFP_KERNEL) != anchor_id);

	do {
		int id = 0;
		void *entry = idr_get_next(&find_idr, &id);
		BUG_ON(entry != xa_mk_value(id));
	} while (time(NULL) < start + 11);

	pthread_join(throbber, NULL);

	idr_remove(&find_idr, anchor_id);
	BUG_ON(!idr_is_empty(&find_idr));
}