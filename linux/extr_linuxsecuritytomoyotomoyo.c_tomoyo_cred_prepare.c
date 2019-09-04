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
struct tomoyo_domain_info {int /*<<< orphan*/  users; } ;
struct cred {struct tomoyo_domain_info* security; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tomoyo_cred_prepare(struct cred *new, const struct cred *old,
			       gfp_t gfp)
{
	struct tomoyo_domain_info *domain = old->security;
	new->security = domain;
	if (domain)
		atomic_inc(&domain->users);
	return 0;
}