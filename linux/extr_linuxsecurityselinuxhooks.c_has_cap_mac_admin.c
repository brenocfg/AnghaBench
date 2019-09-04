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

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_ADMIN ; 
 int SECURITY_CAP_AUDIT ; 
 int SECURITY_CAP_NOAUDIT ; 
 scalar_t__ cap_capable (struct cred const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cred_has_capability (struct cred const*,int /*<<< orphan*/ ,int,int) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static bool has_cap_mac_admin(bool audit)
{
	const struct cred *cred = current_cred();
	int cap_audit = audit ? SECURITY_CAP_AUDIT : SECURITY_CAP_NOAUDIT;

	if (cap_capable(cred, &init_user_ns, CAP_MAC_ADMIN, cap_audit))
		return false;
	if (cred_has_capability(cred, CAP_MAC_ADMIN, cap_audit, true))
		return false;
	return true;
}