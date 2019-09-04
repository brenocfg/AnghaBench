#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct user_datum {int /*<<< orphan*/  roles; } ;
struct role_datum {int /*<<< orphan*/  types; } ;
struct TYPE_6__ {scalar_t__ nprim; } ;
struct TYPE_5__ {int nprim; } ;
struct TYPE_4__ {int nprim; } ;
struct policydb {struct user_datum** user_val_to_struct; struct role_datum** role_val_to_struct; TYPE_3__ p_types; TYPE_2__ p_users; TYPE_1__ p_roles; } ;
struct context {int role; int user; scalar_t__ type; } ;

/* Variables and functions */
 int OBJECT_R_VAL ; 
 int /*<<< orphan*/  ebitmap_get_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mls_context_isvalid (struct policydb*,struct context*) ; 

int policydb_context_isvalid(struct policydb *p, struct context *c)
{
	struct role_datum *role;
	struct user_datum *usrdatum;

	if (!c->role || c->role > p->p_roles.nprim)
		return 0;

	if (!c->user || c->user > p->p_users.nprim)
		return 0;

	if (!c->type || c->type > p->p_types.nprim)
		return 0;

	if (c->role != OBJECT_R_VAL) {
		/*
		 * Role must be authorized for the type.
		 */
		role = p->role_val_to_struct[c->role - 1];
		if (!role || !ebitmap_get_bit(&role->types, c->type - 1))
			/* role may not be associated with type */
			return 0;

		/*
		 * User must be authorized for the role.
		 */
		usrdatum = p->user_val_to_struct[c->user - 1];
		if (!usrdatum)
			return 0;

		if (!ebitmap_get_bit(&usrdatum->roles, c->role - 1))
			/* user may not be associated with role */
			return 0;
	}

	if (!mls_context_isvalid(p, c))
		return 0;

	return 1;
}