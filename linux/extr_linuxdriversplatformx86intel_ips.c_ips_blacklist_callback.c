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
struct dmi_system_id {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ips_blacklist_callback(const struct dmi_system_id *id)
{
	pr_info("Blacklisted intel_ips for %s\n", id->ident);
	return 1;
}