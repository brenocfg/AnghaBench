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
struct TYPE_2__ {struct group_info* cr_group_info; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct svc_rqst {TYPE_1__ rq_cred; } ;
struct svc_export {int /*<<< orphan*/  ex_anon_gid; int /*<<< orphan*/  ex_anon_uid; } ;
struct group_info {int ngroups; int /*<<< orphan*/ * gid; } ;
struct cred {int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  cap_effective; int /*<<< orphan*/  fsuid; int /*<<< orphan*/  fsgid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  INVALID_UID ; 
 int NFSEXP_ALLSQUASH ; 
 int NFSEXP_ROOTSQUASH ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  cap_drop_nfsd_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_raise_nfsd_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_real_cred () ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 struct group_info* get_group_info (struct group_info*) ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct group_info* groups_alloc (int) ; 
 int /*<<< orphan*/  groups_sort (struct group_info*) ; 
 int nfsexp_flags (struct svc_rqst*,struct svc_export*) ; 
 struct cred* override_creds (struct cred*) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int /*<<< orphan*/  put_group_info (struct group_info*) ; 
 int /*<<< orphan*/  revert_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_groups (struct cred*,struct group_info*) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_process_creds () ; 

int nfsd_setuser(struct svc_rqst *rqstp, struct svc_export *exp)
{
	struct group_info *rqgi;
	struct group_info *gi;
	struct cred *new;
	int i;
	int flags = nfsexp_flags(rqstp, exp);

	validate_process_creds();

	/* discard any old override before preparing the new set */
	revert_creds(get_cred(current_real_cred()));
	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	new->fsuid = rqstp->rq_cred.cr_uid;
	new->fsgid = rqstp->rq_cred.cr_gid;

	rqgi = rqstp->rq_cred.cr_group_info;

	if (flags & NFSEXP_ALLSQUASH) {
		new->fsuid = exp->ex_anon_uid;
		new->fsgid = exp->ex_anon_gid;
		gi = groups_alloc(0);
		if (!gi)
			goto oom;
	} else if (flags & NFSEXP_ROOTSQUASH) {
		if (uid_eq(new->fsuid, GLOBAL_ROOT_UID))
			new->fsuid = exp->ex_anon_uid;
		if (gid_eq(new->fsgid, GLOBAL_ROOT_GID))
			new->fsgid = exp->ex_anon_gid;

		gi = groups_alloc(rqgi->ngroups);
		if (!gi)
			goto oom;

		for (i = 0; i < rqgi->ngroups; i++) {
			if (gid_eq(GLOBAL_ROOT_GID, rqgi->gid[i]))
				gi->gid[i] = exp->ex_anon_gid;
			else
				gi->gid[i] = rqgi->gid[i];
		}

		/* Each thread allocates its own gi, no race */
		groups_sort(gi);
	} else {
		gi = get_group_info(rqgi);
	}

	if (uid_eq(new->fsuid, INVALID_UID))
		new->fsuid = exp->ex_anon_uid;
	if (gid_eq(new->fsgid, INVALID_GID))
		new->fsgid = exp->ex_anon_gid;

	set_groups(new, gi);
	put_group_info(gi);

	if (!uid_eq(new->fsuid, GLOBAL_ROOT_UID))
		new->cap_effective = cap_drop_nfsd_set(new->cap_effective);
	else
		new->cap_effective = cap_raise_nfsd_set(new->cap_effective,
							new->cap_permitted);
	validate_process_creds();
	put_cred(override_creds(new));
	put_cred(new);
	validate_process_creds();
	return 0;

oom:
	abort_creds(new);
	return -ENOMEM;
}