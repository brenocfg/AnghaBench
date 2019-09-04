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
struct rcu_segcblist {long len; long len_lazy; } ;

/* Variables and functions */

__attribute__((used)) static inline long rcu_segcblist_n_nonlazy_cbs(struct rcu_segcblist *rsclp)
{
	return rsclp->len - rsclp->len_lazy;
}