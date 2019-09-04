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
typedef  int /*<<< orphan*/  t_key ;
struct key_vector {int /*<<< orphan*/ * tnode; } ;

/* Variables and functions */
 scalar_t__ IS_TRIE (struct key_vector*) ; 
 int /*<<< orphan*/  get_index (int /*<<< orphan*/ ,struct key_vector*) ; 
 int /*<<< orphan*/  put_child (struct key_vector*,int /*<<< orphan*/ ,struct key_vector*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct key_vector*) ; 

__attribute__((used)) static inline void put_child_root(struct key_vector *tp, t_key key,
				  struct key_vector *n)
{
	if (IS_TRIE(tp))
		rcu_assign_pointer(tp->tnode[0], n);
	else
		put_child(tp, get_index(key, tp), n);
}