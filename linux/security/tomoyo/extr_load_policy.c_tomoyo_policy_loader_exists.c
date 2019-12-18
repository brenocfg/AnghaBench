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
struct path {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONFIG_SECURITY_TOMOYO_POLICY_LOADER ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 scalar_t__ kern_path (scalar_t__,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 scalar_t__ tomoyo_loader ; 

__attribute__((used)) static bool tomoyo_policy_loader_exists(void)
{
	struct path path;

	if (!tomoyo_loader)
		tomoyo_loader = CONFIG_SECURITY_TOMOYO_POLICY_LOADER;
	if (kern_path(tomoyo_loader, LOOKUP_FOLLOW, &path)) {
		pr_info("Not activating Mandatory Access Control as %s does not exist.\n",
			tomoyo_loader);
		return false;
	}
	path_put(&path);
	return true;
}