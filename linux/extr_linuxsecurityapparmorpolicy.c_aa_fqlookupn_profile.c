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
struct aa_profile {int dummy; } ;
struct aa_ns {int /*<<< orphan*/  unconfined; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_profile* aa_get_newest_profile (int /*<<< orphan*/ ) ; 
 struct aa_ns* aa_get_ns (int /*<<< orphan*/ ) ; 
 struct aa_ns* aa_lookupn_ns (int /*<<< orphan*/ ,char const*,size_t) ; 
 struct aa_profile* aa_lookupn_profile (struct aa_ns*,char const*,size_t) ; 
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 char* aa_splitn_fqname (char const*,size_t,char const**,size_t*) ; 
 int /*<<< orphan*/  labels_ns (struct aa_label*) ; 

struct aa_profile *aa_fqlookupn_profile(struct aa_label *base,
					const char *fqname, size_t n)
{
	struct aa_profile *profile;
	struct aa_ns *ns;
	const char *name, *ns_name;
	size_t ns_len;

	name = aa_splitn_fqname(fqname, n, &ns_name, &ns_len);
	if (ns_name) {
		ns = aa_lookupn_ns(labels_ns(base), ns_name, ns_len);
		if (!ns)
			return NULL;
	} else
		ns = aa_get_ns(labels_ns(base));

	if (name)
		profile = aa_lookupn_profile(ns, name, n - (name - fqname));
	else if (ns)
		/* default profile for ns, currently unconfined */
		profile = aa_get_newest_profile(ns->unconfined);
	else
		profile = NULL;
	aa_put_ns(ns);

	return profile;
}