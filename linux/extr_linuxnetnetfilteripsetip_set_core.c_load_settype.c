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

/* Variables and functions */
 int /*<<< orphan*/  NFNL_SUBSYS_IPSET ; 
 int /*<<< orphan*/  nfnl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnl_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 scalar_t__ request_module (char*,char const*) ; 

__attribute__((used)) static bool
load_settype(const char *name)
{
	nfnl_unlock(NFNL_SUBSYS_IPSET);
	pr_debug("try to load ip_set_%s\n", name);
	if (request_module("ip_set_%s", name) < 0) {
		pr_warn("Can't find ip_set type %s\n", name);
		nfnl_lock(NFNL_SUBSYS_IPSET);
		return false;
	}
	nfnl_lock(NFNL_SUBSYS_IPSET);
	return true;
}