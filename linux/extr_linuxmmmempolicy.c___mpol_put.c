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
struct mempolicy {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mempolicy*) ; 
 int /*<<< orphan*/  policy_cache ; 

void __mpol_put(struct mempolicy *p)
{
	if (!atomic_dec_and_test(&p->refcnt))
		return;
	kmem_cache_free(policy_cache, p);
}