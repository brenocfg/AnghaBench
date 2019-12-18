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
struct map_groups {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_groups__delete (struct map_groups*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void map_groups__put(struct map_groups *mg)
{
	if (mg && refcount_dec_and_test(&mg->refcnt))
		map_groups__delete(mg);
}