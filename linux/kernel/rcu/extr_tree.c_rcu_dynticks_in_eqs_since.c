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
struct rcu_data {int dummy; } ;

/* Variables and functions */
 int rcu_dynticks_snap (struct rcu_data*) ; 

__attribute__((used)) static bool rcu_dynticks_in_eqs_since(struct rcu_data *rdp, int snap)
{
	return snap != rcu_dynticks_snap(rdp);
}