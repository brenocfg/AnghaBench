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
struct aa_policy {char* hname; int /*<<< orphan*/  profiles; int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 char* aa_str_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

bool aa_policy_init(struct aa_policy *policy, const char *prefix,
		    const char *name, gfp_t gfp)
{
	char *hname;

	/* freed by policy_free */
	if (prefix) {
		hname = aa_str_alloc(strlen(prefix) + strlen(name) + 3, gfp);
		if (hname)
			sprintf(hname, "%s//%s", prefix, name);
	} else {
		hname = aa_str_alloc(strlen(name) + 1, gfp);
		if (hname)
			strcpy(hname, name);
	}
	if (!hname)
		return false;
	policy->hname = hname;
	/* base.name is a substring of fqname */
	policy->name = basename(policy->hname);
	INIT_LIST_HEAD(&policy->list);
	INIT_LIST_HEAD(&policy->profiles);

	return true;
}