#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct module {int dummy; } ;
struct inet_timewait_sock {TYPE_2__* tw_prot; } ;
struct TYPE_4__ {TYPE_1__* twsk_prot; int /*<<< orphan*/  name; struct module* owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  twsk_slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  twsk_destructor (struct sock*) ; 

void inet_twsk_free(struct inet_timewait_sock *tw)
{
	struct module *owner = tw->tw_prot->owner;
	twsk_destructor((struct sock *)tw);
#ifdef SOCK_REFCNT_DEBUG
	pr_debug("%s timewait_sock %p released\n", tw->tw_prot->name, tw);
#endif
	kmem_cache_free(tw->tw_prot->twsk_prot->twsk_slab, tw);
	module_put(owner);
}