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
typedef  int /*<<< orphan*/  u32 ;
struct auth_domain {struct gss_domain* name; int /*<<< orphan*/ * flavour; int /*<<< orphan*/  ref; } ;
struct gss_domain {struct auth_domain h; int /*<<< orphan*/  pseudoflavor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct auth_domain* auth_domain_lookup (char*,struct auth_domain*) ; 
 int /*<<< orphan*/  auth_domain_put (struct auth_domain*) ; 
 int /*<<< orphan*/  kfree (struct gss_domain*) ; 
 struct gss_domain* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gss_domain* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcauthops_gss ; 

int
svcauth_gss_register_pseudoflavor(u32 pseudoflavor, char * name)
{
	struct gss_domain	*new;
	struct auth_domain	*test;
	int			stat = -ENOMEM;

	new = kmalloc(sizeof(*new), GFP_KERNEL);
	if (!new)
		goto out;
	kref_init(&new->h.ref);
	new->h.name = kstrdup(name, GFP_KERNEL);
	if (!new->h.name)
		goto out_free_dom;
	new->h.flavour = &svcauthops_gss;
	new->pseudoflavor = pseudoflavor;

	stat = 0;
	test = auth_domain_lookup(name, &new->h);
	if (test != &new->h) { /* Duplicate registration */
		auth_domain_put(test);
		kfree(new->h.name);
		goto out_free_dom;
	}
	return 0;

out_free_dom:
	kfree(new);
out:
	return stat;
}