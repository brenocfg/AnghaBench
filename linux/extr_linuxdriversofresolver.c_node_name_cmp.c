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
 char* kbasename (int /*<<< orphan*/ ) ; 
 int of_node_cmp (char const*,char const*) ; 

__attribute__((used)) static int node_name_cmp(const struct device_node *dn1,
		const struct device_node *dn2)
{
	const char *n1 = kbasename(dn1->full_name);
	const char *n2 = kbasename(dn2->full_name);

	return of_node_cmp(n1, n2);
}