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
struct sp_node {int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sp_node*) ; 
 int /*<<< orphan*/  mpol_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_cache ; 

__attribute__((used)) static void sp_free(struct sp_node *n)
{
	mpol_put(n->policy);
	kmem_cache_free(sn_cache, n);
}