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
struct rcu_string {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct rcu_string*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static inline void rcu_string_free(struct rcu_string *str)
{
	if (str)
		kfree_rcu(str, rcu);
}