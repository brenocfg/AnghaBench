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
struct aa_proxy {int dummy; } ;
struct aa_label {struct aa_proxy* proxy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aa_proxy_redirect (struct aa_label*,struct aa_label*) ; 
 struct aa_proxy* aa_get_proxy (struct aa_proxy*) ; 
 int /*<<< orphan*/  aa_put_proxy (struct aa_proxy*) ; 

__attribute__((used)) static void __proxy_share(struct aa_label *old, struct aa_label *new)
{
	struct aa_proxy *proxy = new->proxy;

	new->proxy = aa_get_proxy(old->proxy);
	__aa_proxy_redirect(old, new);
	aa_put_proxy(proxy);
}