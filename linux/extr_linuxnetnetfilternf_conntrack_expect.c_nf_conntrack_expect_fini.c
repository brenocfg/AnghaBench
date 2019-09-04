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
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_expect_cachep ; 
 int /*<<< orphan*/  nf_ct_expect_hash ; 
 int /*<<< orphan*/  rcu_barrier () ; 

void nf_conntrack_expect_fini(void)
{
	rcu_barrier(); /* Wait for call_rcu() before destroy */
	kmem_cache_destroy(nf_ct_expect_cachep);
	kvfree(nf_ct_expect_hash);
}