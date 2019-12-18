#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mls_range {TYPE_1__* level; } ;
struct TYPE_2__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  ebitmap_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static int range_tr_destroy(void *key, void *datum, void *p)
{
	struct mls_range *rt = datum;

	kfree(key);
	ebitmap_destroy(&rt->level[0].cat);
	ebitmap_destroy(&rt->level[1].cat);
	kfree(datum);
	cond_resched();
	return 0;
}