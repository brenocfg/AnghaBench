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
typedef  size_t u16 ;
struct selinux_mapping {unsigned int num_perms; int /*<<< orphan*/ * perms; int /*<<< orphan*/  value; } ;
struct selinux_map {size_t size; struct selinux_mapping* mapping; } ;
struct security_class_mapping {char* name; int /*<<< orphan*/ ** perms; } ;
struct policydb {scalar_t__ allow_unknown; scalar_t__ reject_unknown; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct selinux_mapping* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct selinux_mapping*) ; 
 int /*<<< orphan*/  pr_info (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  string_to_av_perm (struct policydb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_to_security_class (struct policydb*,char*) ; 

__attribute__((used)) static int selinux_set_mapping(struct policydb *pol,
			       struct security_class_mapping *map,
			       struct selinux_map *out_map)
{
	u16 i, j;
	unsigned k;
	bool print_unknown_handle = false;

	/* Find number of classes in the input mapping */
	if (!map)
		return -EINVAL;
	i = 0;
	while (map[i].name)
		i++;

	/* Allocate space for the class records, plus one for class zero */
	out_map->mapping = kcalloc(++i, sizeof(*out_map->mapping), GFP_ATOMIC);
	if (!out_map->mapping)
		return -ENOMEM;

	/* Store the raw class and permission values */
	j = 0;
	while (map[j].name) {
		struct security_class_mapping *p_in = map + (j++);
		struct selinux_mapping *p_out = out_map->mapping + j;

		/* An empty class string skips ahead */
		if (!strcmp(p_in->name, "")) {
			p_out->num_perms = 0;
			continue;
		}

		p_out->value = string_to_security_class(pol, p_in->name);
		if (!p_out->value) {
			pr_info("SELinux:  Class %s not defined in policy.\n",
			       p_in->name);
			if (pol->reject_unknown)
				goto err;
			p_out->num_perms = 0;
			print_unknown_handle = true;
			continue;
		}

		k = 0;
		while (p_in->perms[k]) {
			/* An empty permission string skips ahead */
			if (!*p_in->perms[k]) {
				k++;
				continue;
			}
			p_out->perms[k] = string_to_av_perm(pol, p_out->value,
							    p_in->perms[k]);
			if (!p_out->perms[k]) {
				pr_info("SELinux:  Permission %s in class %s not defined in policy.\n",
				       p_in->perms[k], p_in->name);
				if (pol->reject_unknown)
					goto err;
				print_unknown_handle = true;
			}

			k++;
		}
		p_out->num_perms = k;
	}

	if (print_unknown_handle)
		pr_info("SELinux: the above unknown classes and permissions will be %s\n",
		       pol->allow_unknown ? "allowed" : "denied");

	out_map->size = i;
	return 0;
err:
	kfree(out_map->mapping);
	out_map->mapping = NULL;
	return -EINVAL;
}