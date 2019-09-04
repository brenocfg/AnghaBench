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
struct tcf_mirred {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcfm_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct net_device* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *tcf_mirred_dev_dereference(struct tcf_mirred *m)
{
	return rcu_dereference_protected(m->tcfm_dev,
					 lockdep_is_held(&m->tcf_lock));
}