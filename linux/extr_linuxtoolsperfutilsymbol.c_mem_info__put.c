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
struct mem_info {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mem_info*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void mem_info__put(struct mem_info *mi)
{
	if (mi && refcount_dec_and_test(&mi->refcnt))
		free(mi);
}