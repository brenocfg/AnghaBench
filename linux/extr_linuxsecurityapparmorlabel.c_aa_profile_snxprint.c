#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* hname; } ;
struct aa_profile {size_t mode; TYPE_1__ base; struct aa_ns* ns; } ;
struct aa_ns {struct aa_profile* unconfined; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int FLAG_HIDDEN_UNCONFINED ; 
 int FLAG_SHOW_MODE ; 
 int FLAG_VIEW_SUBNS ; 
 char const* aa_hidden_ns_name ; 
 char* aa_ns_name (struct aa_ns*,struct aa_ns*,int) ; 
 char** aa_profile_mode_names ; 
 struct aa_ns* profiles_ns (struct aa_profile*) ; 
 int snprintf (char*,size_t,char*,char const*,...) ; 

__attribute__((used)) static int aa_profile_snxprint(char *str, size_t size, struct aa_ns *view,
			       struct aa_profile *profile, int flags,
			       struct aa_ns **prev_ns)
{
	const char *ns_name = NULL;

	AA_BUG(!str && size != 0);
	AA_BUG(!profile);

	if (!view)
		view = profiles_ns(profile);

	if (view != profile->ns &&
	    (!prev_ns || (*prev_ns != profile->ns))) {
		if (prev_ns)
			*prev_ns = profile->ns;
		ns_name = aa_ns_name(view, profile->ns,
				     flags & FLAG_VIEW_SUBNS);
		if (ns_name == aa_hidden_ns_name) {
			if (flags & FLAG_HIDDEN_UNCONFINED)
				return snprintf(str, size, "%s", "unconfined");
			return snprintf(str, size, "%s", ns_name);
		}
	}

	if ((flags & FLAG_SHOW_MODE) && profile != profile->ns->unconfined) {
		const char *modestr = aa_profile_mode_names[profile->mode];

		if (ns_name)
			return snprintf(str, size, ":%s:%s (%s)", ns_name,
					profile->base.hname, modestr);
		return snprintf(str, size, "%s (%s)", profile->base.hname,
				modestr);
	}

	if (ns_name)
		return snprintf(str, size, ":%s:%s", ns_name,
				profile->base.hname);
	return snprintf(str, size, "%s", profile->base.hname);
}