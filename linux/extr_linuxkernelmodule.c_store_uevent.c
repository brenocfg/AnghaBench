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
struct module_kobject {int /*<<< orphan*/  kobj; } ;
struct module_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kobject_synth_uevent (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static ssize_t store_uevent(struct module_attribute *mattr,
			    struct module_kobject *mk,
			    const char *buffer, size_t count)
{
	int rc;

	rc = kobject_synth_uevent(&mk->kobj, buffer, count);
	return rc ? rc : count;
}