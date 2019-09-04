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
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kbasename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

bool of_node_name_prefix(const struct device_node *np, const char *prefix)
{
	if (!np)
		return false;

	return strncmp(kbasename(np->full_name), prefix, strlen(prefix)) == 0;
}