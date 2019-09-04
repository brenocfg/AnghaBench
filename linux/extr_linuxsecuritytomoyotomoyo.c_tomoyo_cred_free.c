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

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tomoyo_cred_free(struct cred *cred)
{
	struct tomoyo_domain_info *domain = cred->security;
	if (domain)
		atomic_dec(&domain->users);
}