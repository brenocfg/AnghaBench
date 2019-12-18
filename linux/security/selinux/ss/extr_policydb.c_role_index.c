#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct role_datum {int value; scalar_t__ bounds; } ;
struct TYPE_2__ {int nprim; } ;
struct policydb {struct role_datum** role_val_to_struct; void*** sym_val_to_name; TYPE_1__ p_roles; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SYM_ROLES ; 

__attribute__((used)) static int role_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct role_datum *role;

	role = datum;
	p = datap;
	if (!role->value
	    || role->value > p->p_roles.nprim
	    || role->bounds > p->p_roles.nprim)
		return -EINVAL;

	p->sym_val_to_name[SYM_ROLES][role->value - 1] = key;
	p->role_val_to_struct[role->value - 1] = role;
	return 0;
}