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
struct aa_ns {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lookup_profile (int /*<<< orphan*/ *,char const*) ; 
 struct aa_profile* aa_get_profile (int /*<<< orphan*/ ) ; 
 int replacement_allowed (struct aa_profile*,int,char const**) ; 

__attribute__((used)) static int __lookup_replace(struct aa_ns *ns, const char *hname,
			    bool noreplace, struct aa_profile **p,
			    const char **info)
{
	*p = aa_get_profile(__lookup_profile(&ns->base, hname));
	if (*p) {
		int error = replacement_allowed(*p, noreplace, info);
		if (error) {
			*info = "profile can not be replaced";
			return error;
		}
	}

	return 0;
}