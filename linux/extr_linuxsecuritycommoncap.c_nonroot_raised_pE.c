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
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 scalar_t__ __cap_full (int /*<<< orphan*/ ,struct cred*) ; 
 scalar_t__ __cap_gained (int /*<<< orphan*/ ,struct cred*,struct cred const*) ; 
 scalar_t__ __cap_grew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*) ; 
 scalar_t__ __is_eff (int /*<<< orphan*/ ,struct cred*) ; 
 scalar_t__ __is_real (int /*<<< orphan*/ ,struct cred*) ; 
 int /*<<< orphan*/  __is_setuid (struct cred*,struct cred const*) ; 
 scalar_t__ __is_suid (int /*<<< orphan*/ ,struct cred*) ; 
 int /*<<< orphan*/  ambient ; 
 int /*<<< orphan*/  effective ; 
 int /*<<< orphan*/  permitted ; 
 scalar_t__ root_privileged () ; 

__attribute__((used)) static inline bool nonroot_raised_pE(struct cred *new, const struct cred *old,
				     kuid_t root, bool has_fcap)
{
	bool ret = false;

	if ((__cap_grew(effective, ambient, new) &&
	     !(__cap_full(effective, new) &&
	       (__is_eff(root, new) || __is_real(root, new)) &&
	       root_privileged())) ||
	    (root_privileged() &&
	     __is_suid(root, new) &&
	     !__cap_full(effective, new)) ||
	    (!__is_setuid(new, old) &&
	     ((has_fcap &&
	       __cap_gained(permitted, new, old)) ||
	      __cap_gained(ambient, new, old))))

		ret = true;

	return ret;
}