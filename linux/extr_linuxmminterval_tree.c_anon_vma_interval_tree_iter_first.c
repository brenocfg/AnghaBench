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
struct rb_root_cached {int dummy; } ;
struct anon_vma_chain {int dummy; } ;

/* Variables and functions */
 struct anon_vma_chain* __anon_vma_interval_tree_iter_first (struct rb_root_cached*,unsigned long,unsigned long) ; 

struct anon_vma_chain *
anon_vma_interval_tree_iter_first(struct rb_root_cached *root,
				  unsigned long first, unsigned long last)
{
	return __anon_vma_interval_tree_iter_first(root, first, last);
}