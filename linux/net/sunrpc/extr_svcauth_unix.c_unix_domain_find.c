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
struct auth_domain {int /*<<< orphan*/ * flavour; int /*<<< orphan*/ * name; int /*<<< orphan*/  ref; } ;
struct unix_domain {struct auth_domain h; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct auth_domain* auth_domain_find (char*) ; 
 struct auth_domain* auth_domain_lookup (char*,struct auth_domain*) ; 
 int /*<<< orphan*/  auth_domain_put (struct auth_domain*) ; 
 int /*<<< orphan*/  kfree (struct unix_domain*) ; 
 struct unix_domain* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcauth_unix ; 
 int /*<<< orphan*/  svcauth_unix_domain_release (struct auth_domain*) ; 

struct auth_domain *unix_domain_find(char *name)
{
	struct auth_domain *rv;
	struct unix_domain *new = NULL;

	rv = auth_domain_find(name);
	while(1) {
		if (rv) {
			if (new && rv != &new->h)
				svcauth_unix_domain_release(&new->h);

			if (rv->flavour != &svcauth_unix) {
				auth_domain_put(rv);
				return NULL;
			}
			return rv;
		}

		new = kmalloc(sizeof(*new), GFP_KERNEL);
		if (new == NULL)
			return NULL;
		kref_init(&new->h.ref);
		new->h.name = kstrdup(name, GFP_KERNEL);
		if (new->h.name == NULL) {
			kfree(new);
			return NULL;
		}
		new->h.flavour = &svcauth_unix;
		rv = auth_domain_lookup(name, &new->h);
	}
}