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
typedef  int /*<<< orphan*/  u32 ;
struct user_datum {scalar_t__ value; } ;
struct type_datum {scalar_t__ value; } ;
struct role_datum {scalar_t__ value; } ;
struct ocontext {scalar_t__* sid; TYPE_4__* context; struct ocontext* next; } ;
struct convert_context_args {TYPE_5__* oldp; int /*<<< orphan*/  state; TYPE_6__* newp; } ;
struct context {char* str; int /*<<< orphan*/  len; scalar_t__ type; scalar_t__ role; scalar_t__ user; } ;
struct TYPE_13__ {int /*<<< orphan*/  table; } ;
struct TYPE_12__ {int /*<<< orphan*/  table; } ;
struct TYPE_11__ {int /*<<< orphan*/  table; } ;
struct TYPE_16__ {struct ocontext** ocontexts; scalar_t__ mls_enabled; TYPE_3__ p_types; TYPE_2__ p_roles; TYPE_1__ p_users; } ;
struct TYPE_15__ {scalar_t__ mls_enabled; } ;
struct TYPE_14__ {int /*<<< orphan*/  range; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t OCON_ISID ; 
 scalar_t__ SECINITSID_UNLABELED ; 
 int /*<<< orphan*/  SECSID_NULL ; 
 int /*<<< orphan*/  SYM_ROLES ; 
 int /*<<< orphan*/  SYM_TYPES ; 
 int /*<<< orphan*/  SYM_USERS ; 
 int /*<<< orphan*/  context_destroy (struct context*) ; 
 int /*<<< orphan*/  context_init (struct context*) ; 
 int context_struct_to_string (TYPE_5__*,struct context*,char**,int /*<<< orphan*/ *) ; 
 int convert_context_handle_invalid_context (int /*<<< orphan*/ ,struct context*) ; 
 void* hashtab_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int mls_convert_context (TYPE_5__*,TYPE_6__*,struct context*,struct context*) ; 
 int mls_range_set (struct context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  policydb_context_isvalid (TYPE_6__*,struct context*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int string_to_context_struct (TYPE_6__*,int /*<<< orphan*/ *,char*,struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_name (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int convert_context(struct context *oldc, struct context *newc, void *p)
{
	struct convert_context_args *args;
	struct ocontext *oc;
	struct role_datum *role;
	struct type_datum *typdatum;
	struct user_datum *usrdatum;
	char *s;
	u32 len;
	int rc;

	args = p;

	if (oldc->str) {
		s = kstrdup(oldc->str, GFP_KERNEL);
		if (!s)
			return -ENOMEM;

		rc = string_to_context_struct(args->newp, NULL, s,
					      newc, SECSID_NULL);
		if (rc == -EINVAL) {
			/*
			 * Retain string representation for later mapping.
			 *
			 * IMPORTANT: We need to copy the contents of oldc->str
			 * back into s again because string_to_context_struct()
			 * may have garbled it.
			 */
			memcpy(s, oldc->str, oldc->len);
			context_init(newc);
			newc->str = s;
			newc->len = oldc->len;
			return 0;
		}
		kfree(s);
		if (rc) {
			/* Other error condition, e.g. ENOMEM. */
			pr_err("SELinux:   Unable to map context %s, rc = %d.\n",
			       oldc->str, -rc);
			return rc;
		}
		pr_info("SELinux:  Context %s became valid (mapped).\n",
			oldc->str);
		return 0;
	}

	context_init(newc);

	/* Convert the user. */
	rc = -EINVAL;
	usrdatum = hashtab_search(args->newp->p_users.table,
				  sym_name(args->oldp,
					   SYM_USERS, oldc->user - 1));
	if (!usrdatum)
		goto bad;
	newc->user = usrdatum->value;

	/* Convert the role. */
	rc = -EINVAL;
	role = hashtab_search(args->newp->p_roles.table,
			      sym_name(args->oldp, SYM_ROLES, oldc->role - 1));
	if (!role)
		goto bad;
	newc->role = role->value;

	/* Convert the type. */
	rc = -EINVAL;
	typdatum = hashtab_search(args->newp->p_types.table,
				  sym_name(args->oldp,
					   SYM_TYPES, oldc->type - 1));
	if (!typdatum)
		goto bad;
	newc->type = typdatum->value;

	/* Convert the MLS fields if dealing with MLS policies */
	if (args->oldp->mls_enabled && args->newp->mls_enabled) {
		rc = mls_convert_context(args->oldp, args->newp, oldc, newc);
		if (rc)
			goto bad;
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
		rc = mls_range_set(newc, &oc->context[0].range);
		if (rc)
			goto bad;
	}

	/* Check the validity of the new context. */
	if (!policydb_context_isvalid(args->newp, newc)) {
		rc = convert_context_handle_invalid_context(args->state, oldc);
		if (rc)
			goto bad;
	}

	return 0;
bad:
	/* Map old representation to string and save it. */
	rc = context_struct_to_string(args->oldp, oldc, &s, &len);
	if (rc)
		return rc;
	context_destroy(newc);
	newc->str = s;
	newc->len = len;
	pr_info("SELinux:  Context %s became invalid (unmapped).\n",
		newc->str);
	return 0;
}