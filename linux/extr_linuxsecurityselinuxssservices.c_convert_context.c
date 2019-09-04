#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct user_datum {scalar_t__ value; } ;
struct type_datum {scalar_t__ value; } ;
struct role_datum {scalar_t__ value; } ;
struct ocontext {scalar_t__* sid; TYPE_4__* context; struct ocontext* next; } ;
struct mls_range {int dummy; } ;
struct convert_context_args {TYPE_5__* oldp; int /*<<< orphan*/  state; TYPE_6__* newp; } ;
struct context {char* str; scalar_t__ len; scalar_t__ type; scalar_t__ role; scalar_t__ user; } ;
struct TYPE_13__ {int /*<<< orphan*/  table; } ;
struct TYPE_12__ {int /*<<< orphan*/  table; } ;
struct TYPE_11__ {int /*<<< orphan*/  table; } ;
struct TYPE_16__ {struct ocontext** ocontexts; scalar_t__ mls_enabled; TYPE_3__ p_types; TYPE_2__ p_roles; TYPE_1__ p_users; } ;
struct TYPE_15__ {scalar_t__ mls_enabled; } ;
struct TYPE_14__ {struct mls_range range; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t OCON_ISID ; 
 scalar_t__ SECINITSID_NUM ; 
 scalar_t__ SECINITSID_UNLABELED ; 
 int /*<<< orphan*/  SECSID_NULL ; 
 int /*<<< orphan*/  SYM_ROLES ; 
 int /*<<< orphan*/  SYM_TYPES ; 
 int /*<<< orphan*/  SYM_USERS ; 
 int context_cpy (struct context*,struct context*) ; 
 int /*<<< orphan*/  context_destroy (struct context*) ; 
 int context_struct_to_string (TYPE_5__*,struct context*,char**,scalar_t__*) ; 
 int convert_context_handle_invalid_context (int /*<<< orphan*/ ,struct context*) ; 
 void* hashtab_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct context*,struct context*,int) ; 
 int /*<<< orphan*/  mls_context_destroy (struct context*) ; 
 int mls_convert_context (TYPE_5__*,TYPE_6__*,struct context*) ; 
 int mls_range_set (struct context*,struct mls_range*) ; 
 int /*<<< orphan*/  policydb_context_isvalid (TYPE_6__*,struct context*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int string_to_context_struct (TYPE_6__*,int /*<<< orphan*/ *,char*,scalar_t__,struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_name (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int convert_context(u32 key,
			   struct context *c,
			   void *p)
{
	struct convert_context_args *args;
	struct context oldc;
	struct ocontext *oc;
	struct mls_range *range;
	struct role_datum *role;
	struct type_datum *typdatum;
	struct user_datum *usrdatum;
	char *s;
	u32 len;
	int rc = 0;

	if (key <= SECINITSID_NUM)
		goto out;

	args = p;

	if (c->str) {
		struct context ctx;

		rc = -ENOMEM;
		s = kstrdup(c->str, GFP_KERNEL);
		if (!s)
			goto out;

		rc = string_to_context_struct(args->newp, NULL, s,
					      c->len, &ctx, SECSID_NULL);
		kfree(s);
		if (!rc) {
			pr_info("SELinux:  Context %s became valid (mapped).\n",
			       c->str);
			/* Replace string with mapped representation. */
			kfree(c->str);
			memcpy(c, &ctx, sizeof(*c));
			goto out;
		} else if (rc == -EINVAL) {
			/* Retain string representation for later mapping. */
			rc = 0;
			goto out;
		} else {
			/* Other error condition, e.g. ENOMEM. */
			pr_err("SELinux:   Unable to map context %s, rc = %d.\n",
			       c->str, -rc);
			goto out;
		}
	}

	rc = context_cpy(&oldc, c);
	if (rc)
		goto out;

	/* Convert the user. */
	rc = -EINVAL;
	usrdatum = hashtab_search(args->newp->p_users.table,
				  sym_name(args->oldp, SYM_USERS, c->user - 1));
	if (!usrdatum)
		goto bad;
	c->user = usrdatum->value;

	/* Convert the role. */
	rc = -EINVAL;
	role = hashtab_search(args->newp->p_roles.table,
			      sym_name(args->oldp, SYM_ROLES, c->role - 1));
	if (!role)
		goto bad;
	c->role = role->value;

	/* Convert the type. */
	rc = -EINVAL;
	typdatum = hashtab_search(args->newp->p_types.table,
				  sym_name(args->oldp, SYM_TYPES, c->type - 1));
	if (!typdatum)
		goto bad;
	c->type = typdatum->value;

	/* Convert the MLS fields if dealing with MLS policies */
	if (args->oldp->mls_enabled && args->newp->mls_enabled) {
		rc = mls_convert_context(args->oldp, args->newp, c);
		if (rc)
			goto bad;
	} else if (args->oldp->mls_enabled && !args->newp->mls_enabled) {
		/*
		 * Switching between MLS and non-MLS policy:
		 * free any storage used by the MLS fields in the
		 * context for all existing entries in the sidtab.
		 */
		mls_context_destroy(c);
	} else if (!args->oldp->mls_enabled && args->newp->mls_enabled) {
		/*
		 * Switching between non-MLS and MLS policy:
		 * ensure that the MLS fields of the context for all
		 * existing entries in the sidtab are filled in with a
		 * suitable default value, likely taken from one of the
		 * initial SIDs.
		 */
		oc = args->newp->ocontexts[OCON_ISID];
		while (oc && oc->sid[0] != SECINITSID_UNLABELED)
			oc = oc->next;
		rc = -EINVAL;
		if (!oc) {
			pr_err("SELinux:  unable to look up"
				" the initial SIDs list\n");
			goto bad;
		}
		range = &oc->context[0].range;
		rc = mls_range_set(c, range);
		if (rc)
			goto bad;
	}

	/* Check the validity of the new context. */
	if (!policydb_context_isvalid(args->newp, c)) {
		rc = convert_context_handle_invalid_context(args->state,
							    &oldc);
		if (rc)
			goto bad;
	}

	context_destroy(&oldc);

	rc = 0;
out:
	return rc;
bad:
	/* Map old representation to string and save it. */
	rc = context_struct_to_string(args->oldp, &oldc, &s, &len);
	if (rc)
		return rc;
	context_destroy(&oldc);
	context_destroy(c);
	c->str = s;
	c->len = len;
	pr_info("SELinux:  Context %s became invalid (unmapped).\n",
	       c->str);
	rc = 0;
	goto out;
}