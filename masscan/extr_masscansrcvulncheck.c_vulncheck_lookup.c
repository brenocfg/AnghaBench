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
struct MassVulnCheck {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct MassVulnCheck vuln_ntp_monlist ; 

struct MassVulnCheck *
vulncheck_lookup(const char *name)
{
    if (strcmp(name, vuln_ntp_monlist.name) == 0)
        return &vuln_ntp_monlist;
    return 0;
}