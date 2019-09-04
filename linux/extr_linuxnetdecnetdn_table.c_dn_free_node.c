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
struct dn_fib_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_FIB_INFO (struct dn_fib_node*) ; 
 int /*<<< orphan*/  dn_fib_release_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_hash_kmem ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dn_fib_node*) ; 

__attribute__((used)) static void dn_free_node(struct dn_fib_node *f)
{
	dn_fib_release_info(DN_FIB_INFO(f));
	kmem_cache_free(dn_hash_kmem, f);
}