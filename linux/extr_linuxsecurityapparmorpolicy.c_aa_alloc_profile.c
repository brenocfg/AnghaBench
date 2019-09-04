#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aa_proxy {int dummy; } ;
struct TYPE_5__ {struct aa_profile** vec; int /*<<< orphan*/  flags; int /*<<< orphan*/  hname; struct aa_proxy* proxy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hname; } ;
struct aa_profile {TYPE_2__ label; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_PROFILE ; 
 struct aa_proxy* aa_alloc_proxy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_free_profile (struct aa_profile*) ; 
 int /*<<< orphan*/  aa_get_proxy (struct aa_proxy*) ; 
 int /*<<< orphan*/  aa_label_init (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_policy_init (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 struct aa_profile* kzalloc (int,int /*<<< orphan*/ ) ; 

struct aa_profile *aa_alloc_profile(const char *hname, struct aa_proxy *proxy,
				    gfp_t gfp)
{
	struct aa_profile *profile;

	/* freed by free_profile - usually through aa_put_profile */
	profile = kzalloc(sizeof(*profile) + sizeof(struct aa_profile *) * 2,
			  gfp);
	if (!profile)
		return NULL;

	if (!aa_policy_init(&profile->base, NULL, hname, gfp))
		goto fail;
	if (!aa_label_init(&profile->label, 1, gfp))
		goto fail;

	/* update being set needed by fs interface */
	if (!proxy) {
		proxy = aa_alloc_proxy(&profile->label, gfp);
		if (!proxy)
			goto fail;
	} else
		aa_get_proxy(proxy);
	profile->label.proxy = proxy;

	profile->label.hname = profile->base.hname;
	profile->label.flags |= FLAG_PROFILE;
	profile->label.vec[0] = profile;

	/* refcount released by caller */
	return profile;

fail:
	aa_free_profile(profile);

	return NULL;
}