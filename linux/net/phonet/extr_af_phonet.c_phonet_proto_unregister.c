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
struct phonet_protocol {int /*<<< orphan*/  prot; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct phonet_protocol const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct phonet_protocol const** proto_tab ; 
 int /*<<< orphan*/  proto_tab_lock ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void phonet_proto_unregister(unsigned int protocol,
			const struct phonet_protocol *pp)
{
	mutex_lock(&proto_tab_lock);
	BUG_ON(proto_tab[protocol] != pp);
	RCU_INIT_POINTER(proto_tab[protocol], NULL);
	mutex_unlock(&proto_tab_lock);
	synchronize_rcu();
	proto_unregister(pp->prot);
}