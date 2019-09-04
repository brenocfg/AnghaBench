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
struct key_vector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct key_vector*) ; 
 TYPE_1__* tn_info (struct key_vector*) ; 

__attribute__((used)) static inline void node_set_parent(struct key_vector *n, struct key_vector *tp)
{
	if (n)
		rcu_assign_pointer(tn_info(n)->parent, tp);
}