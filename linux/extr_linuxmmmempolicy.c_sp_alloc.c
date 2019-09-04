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
struct sp_node {int dummy; } ;
struct mempolicy {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 int /*<<< orphan*/  MPOL_F_SHARED ; 
 struct sp_node* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sp_node*) ; 
 struct mempolicy* mpol_dup (struct mempolicy*) ; 
 int /*<<< orphan*/  sn_cache ; 
 int /*<<< orphan*/  sp_node_init (struct sp_node*,unsigned long,unsigned long,struct mempolicy*) ; 

__attribute__((used)) static struct sp_node *sp_alloc(unsigned long start, unsigned long end,
				struct mempolicy *pol)
{
	struct sp_node *n;
	struct mempolicy *newpol;

	n = kmem_cache_alloc(sn_cache, GFP_KERNEL);
	if (!n)
		return NULL;

	newpol = mpol_dup(pol);
	if (IS_ERR(newpol)) {
		kmem_cache_free(sn_cache, n);
		return NULL;
	}
	newpol->flags |= MPOL_F_SHARED;
	sp_node_init(n, start, end, newpol);

	return n;
}