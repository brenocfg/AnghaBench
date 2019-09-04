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
struct sidtab {int dummy; } ;
struct policydb {struct ocontext** ocontexts; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct ocontext {TYPE_1__ u; TYPE_2__* context; int /*<<< orphan*/ * sid; struct ocontext* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t OCON_ISID ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int sidtab_init (struct sidtab*) ; 
 int sidtab_insert (struct sidtab*,int /*<<< orphan*/ ,TYPE_2__*) ; 

int policydb_load_isids(struct policydb *p, struct sidtab *s)
{
	struct ocontext *head, *c;
	int rc;

	rc = sidtab_init(s);
	if (rc) {
		pr_err("SELinux:  out of memory on SID table init\n");
		goto out;
	}

	head = p->ocontexts[OCON_ISID];
	for (c = head; c; c = c->next) {
		rc = -EINVAL;
		if (!c->context[0].user) {
			pr_err("SELinux:  SID %s was never defined.\n",
				c->u.name);
			goto out;
		}

		rc = sidtab_insert(s, c->sid[0], &c->context[0]);
		if (rc) {
			pr_err("SELinux:  unable to load initial SID %s.\n",
				c->u.name);
			goto out;
		}
	}
	rc = 0;
out:
	return rc;
}