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
typedef  int /*<<< orphan*/  u32 ;
struct user_datum {int /*<<< orphan*/  value; } ;
struct type_datum {int /*<<< orphan*/  value; scalar_t__ attribute; } ;
struct sidtab {int dummy; } ;
struct role_datum {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct policydb {TYPE_3__ p_types; TYPE_2__ p_roles; TYPE_1__ p_users; } ;
struct context {int /*<<< orphan*/  type; int /*<<< orphan*/  role; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  context_destroy (struct context*) ; 
 int /*<<< orphan*/  context_init (struct context*) ; 
 void* hashtab_search (int /*<<< orphan*/ ,char*) ; 
 int mls_context_to_sid (struct policydb*,char,char*,struct context*,struct sidtab*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policydb_context_isvalid (struct policydb*,struct context*) ; 

__attribute__((used)) static int string_to_context_struct(struct policydb *pol,
				    struct sidtab *sidtabp,
				    char *scontext,
				    struct context *ctx,
				    u32 def_sid)
{
	struct role_datum *role;
	struct type_datum *typdatum;
	struct user_datum *usrdatum;
	char *scontextp, *p, oldc;
	int rc = 0;

	context_init(ctx);

	/* Parse the security context. */

	rc = -EINVAL;
	scontextp = (char *) scontext;

	/* Extract the user. */
	p = scontextp;
	while (*p && *p != ':')
		p++;

	if (*p == 0)
		goto out;

	*p++ = 0;

	usrdatum = hashtab_search(pol->p_users.table, scontextp);
	if (!usrdatum)
		goto out;

	ctx->user = usrdatum->value;

	/* Extract role. */
	scontextp = p;
	while (*p && *p != ':')
		p++;

	if (*p == 0)
		goto out;

	*p++ = 0;

	role = hashtab_search(pol->p_roles.table, scontextp);
	if (!role)
		goto out;
	ctx->role = role->value;

	/* Extract type. */
	scontextp = p;
	while (*p && *p != ':')
		p++;
	oldc = *p;
	*p++ = 0;

	typdatum = hashtab_search(pol->p_types.table, scontextp);
	if (!typdatum || typdatum->attribute)
		goto out;

	ctx->type = typdatum->value;

	rc = mls_context_to_sid(pol, oldc, p, ctx, sidtabp, def_sid);
	if (rc)
		goto out;

	/* Check the validity of the new context. */
	rc = -EINVAL;
	if (!policydb_context_isvalid(pol, ctx))
		goto out;
	rc = 0;
out:
	if (rc)
		context_destroy(ctx);
	return rc;
}