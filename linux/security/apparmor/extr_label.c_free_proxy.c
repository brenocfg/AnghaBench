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
struct aa_proxy {int /*<<< orphan*/  label; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 scalar_t__ PROXY_POISON ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aa_proxy*) ; 
 int /*<<< orphan*/  memset (struct aa_proxy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_proxy(struct aa_proxy *proxy)
{
	if (proxy) {
		/* p->label will not updated any more as p is dead */
		aa_put_label(rcu_dereference_protected(proxy->label, true));
		memset(proxy, 0, sizeof(*proxy));
		RCU_INIT_POINTER(proxy->label, (struct aa_label *)PROXY_POISON);
		kfree(proxy);
	}
}