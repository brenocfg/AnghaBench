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
struct ip_set_type {scalar_t__ protocol; int /*<<< orphan*/  revision_max; int /*<<< orphan*/  revision_min; int /*<<< orphan*/  family; int /*<<< orphan*/  name; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPSET_PROTOCOL ; 
 int /*<<< orphan*/  family_name (int /*<<< orphan*/ ) ; 
 scalar_t__ find_set_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_type_list ; 
 int /*<<< orphan*/  ip_set_type_lock () ; 
 int /*<<< orphan*/  ip_set_type_unlock () ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int
ip_set_type_register(struct ip_set_type *type)
{
	int ret = 0;

	if (type->protocol != IPSET_PROTOCOL) {
		pr_warn("ip_set type %s, family %s, revision %u:%u uses wrong protocol version %u (want %u)\n",
			type->name, family_name(type->family),
			type->revision_min, type->revision_max,
			type->protocol, IPSET_PROTOCOL);
		return -EINVAL;
	}

	ip_set_type_lock();
	if (find_set_type(type->name, type->family, type->revision_min)) {
		/* Duplicate! */
		pr_warn("ip_set type %s, family %s with revision min %u already registered!\n",
			type->name, family_name(type->family),
			type->revision_min);
		ip_set_type_unlock();
		return -EINVAL;
	}
	list_add_rcu(&type->list, &ip_set_type_list);
	pr_debug("type %s, family %s, revision %u:%u registered.\n",
		 type->name, family_name(type->family),
		 type->revision_min, type->revision_max);
	ip_set_type_unlock();

	return ret;
}