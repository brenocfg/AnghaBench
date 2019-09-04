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
struct policydb {struct role_datum** role_val_to_struct; struct flex_array** sym_val_to_name; TYPE_1__ p_roles; } ;
struct flex_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int GFP_KERNEL ; 
 size_t SYM_ROLES ; 
 int __GFP_ZERO ; 
 scalar_t__ flex_array_put_ptr (struct flex_array*,int,void*,int) ; 

__attribute__((used)) static int role_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct role_datum *role;
	struct flex_array *fa;

	role = datum;
	p = datap;
	if (!role->value
	    || role->value > p->p_roles.nprim
	    || role->bounds > p->p_roles.nprim)
		return -EINVAL;

	fa = p->sym_val_to_name[SYM_ROLES];
	if (flex_array_put_ptr(fa, role->value - 1, key,
			       GFP_KERNEL | __GFP_ZERO))
		BUG();
	p->role_val_to_struct[role->value - 1] = role;
	return 0;
}