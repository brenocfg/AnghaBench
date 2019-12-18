#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_7__ {scalar_t__ expiry_time; scalar_t__ flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  cr_principal; struct gss_api_mech* cr_gss_mech; TYPE_2__* cr_group_info; void* cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct rsc {TYPE_4__ h; TYPE_1__ cred; int /*<<< orphan*/  mechctx; int /*<<< orphan*/  handle; } ;
struct gss_api_mech {int dummy; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  rsci ;
typedef  void* kgid_t ;
struct TYPE_6__ {void** gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NGROUPS_MAX ; 
 int /*<<< orphan*/  cache_put (TYPE_4__*,struct cache_detail*) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 scalar_t__ dup_to_netobj (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ get_expiry (char**) ; 
 int get_int (char**,int*) ; 
 int /*<<< orphan*/  gid_valid (void*) ; 
 TYPE_2__* groups_alloc (int) ; 
 int /*<<< orphan*/  groups_sort (TYPE_2__*) ; 
 int gss_import_sec_context (char*,int,struct gss_api_mech*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gss_api_mech* gss_mech_get_by_name (char*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 void* make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct rsc*,int /*<<< orphan*/ ,int) ; 
 int qword_get (char**,char*,int) ; 
 int /*<<< orphan*/  rsc_free (struct rsc*) ; 
 struct rsc* rsc_lookup (struct cache_detail*,struct rsc*) ; 
 struct rsc* rsc_update (struct cache_detail*,struct rsc*,struct rsc*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int rsc_parse(struct cache_detail *cd,
		     char *mesg, int mlen)
{
	/* contexthandle expiry [ uid gid N <n gids> mechname ...mechdata... ] */
	char *buf = mesg;
	int id;
	int len, rv;
	struct rsc rsci, *rscp = NULL;
	time_t expiry;
	int status = -EINVAL;
	struct gss_api_mech *gm = NULL;

	memset(&rsci, 0, sizeof(rsci));
	/* context handle */
	len = qword_get(&mesg, buf, mlen);
	if (len < 0) goto out;
	status = -ENOMEM;
	if (dup_to_netobj(&rsci.handle, buf, len))
		goto out;

	rsci.h.flags = 0;
	/* expiry */
	expiry = get_expiry(&mesg);
	status = -EINVAL;
	if (expiry == 0)
		goto out;

	rscp = rsc_lookup(cd, &rsci);
	if (!rscp)
		goto out;

	/* uid, or NEGATIVE */
	rv = get_int(&mesg, &id);
	if (rv == -EINVAL)
		goto out;
	if (rv == -ENOENT)
		set_bit(CACHE_NEGATIVE, &rsci.h.flags);
	else {
		int N, i;

		/*
		 * NOTE: we skip uid_valid()/gid_valid() checks here:
		 * instead, * -1 id's are later mapped to the
		 * (export-specific) anonymous id by nfsd_setuser.
		 *
		 * (But supplementary gid's get no such special
		 * treatment so are checked for validity here.)
		 */
		/* uid */
		rsci.cred.cr_uid = make_kuid(current_user_ns(), id);

		/* gid */
		if (get_int(&mesg, &id))
			goto out;
		rsci.cred.cr_gid = make_kgid(current_user_ns(), id);

		/* number of additional gid's */
		if (get_int(&mesg, &N))
			goto out;
		if (N < 0 || N > NGROUPS_MAX)
			goto out;
		status = -ENOMEM;
		rsci.cred.cr_group_info = groups_alloc(N);
		if (rsci.cred.cr_group_info == NULL)
			goto out;

		/* gid's */
		status = -EINVAL;
		for (i=0; i<N; i++) {
			kgid_t kgid;
			if (get_int(&mesg, &id))
				goto out;
			kgid = make_kgid(current_user_ns(), id);
			if (!gid_valid(kgid))
				goto out;
			rsci.cred.cr_group_info->gid[i] = kgid;
		}
		groups_sort(rsci.cred.cr_group_info);

		/* mech name */
		len = qword_get(&mesg, buf, mlen);
		if (len < 0)
			goto out;
		gm = rsci.cred.cr_gss_mech = gss_mech_get_by_name(buf);
		status = -EOPNOTSUPP;
		if (!gm)
			goto out;

		status = -EINVAL;
		/* mech-specific data: */
		len = qword_get(&mesg, buf, mlen);
		if (len < 0)
			goto out;
		status = gss_import_sec_context(buf, len, gm, &rsci.mechctx,
						NULL, GFP_KERNEL);
		if (status)
			goto out;

		/* get client name */
		len = qword_get(&mesg, buf, mlen);
		if (len > 0) {
			rsci.cred.cr_principal = kstrdup(buf, GFP_KERNEL);
			if (!rsci.cred.cr_principal) {
				status = -ENOMEM;
				goto out;
			}
		}

	}
	rsci.h.expiry_time = expiry;
	rscp = rsc_update(cd, &rsci, rscp);
	status = 0;
out:
	rsc_free(&rsci);
	if (rscp)
		cache_put(&rscp->h, cd);
	else
		status = -ENOMEM;
	return status;
}