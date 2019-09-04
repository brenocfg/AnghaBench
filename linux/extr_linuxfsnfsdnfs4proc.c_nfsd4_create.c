#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_6__ {int /*<<< orphan*/  ia_valid; } ;
struct nfsd4_create {int cr_type; int /*<<< orphan*/  cr_cinfo; int /*<<< orphan*/  cr_bmval; int /*<<< orphan*/ * cr_acl; TYPE_3__ cr_label; TYPE_2__ cr_iattr; int /*<<< orphan*/  cr_namelen; int /*<<< orphan*/  cr_name; int /*<<< orphan*/  cr_specdata2; int /*<<< orphan*/  cr_specdata1; int /*<<< orphan*/  cr_data; scalar_t__ cr_umask; } ;
union nfsd4_op_u {struct nfsd4_create create; } ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_8__ {TYPE_1__* fs; } ;
struct TYPE_5__ {scalar_t__ umask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SIZE ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NF4BLK 133 
#define  NF4CHR 132 
#define  NF4DIR 131 
#define  NF4FIFO 130 
#define  NF4LNK 129 
#define  NF4SOCK 128 
 int /*<<< orphan*/  NFS4_FHSIZE ; 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFIFO ; 
 int /*<<< orphan*/  S_IFSOCK ; 
 scalar_t__ check_attr_support (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  do_set_nfs4_acl (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_dup2 (int /*<<< orphan*/ *,struct svc_fh*) ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ fh_verify (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_security_inode_setsecctx (struct svc_fh*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_attrmask ; 
 scalar_t__ nfsd_create (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct svc_fh*) ; 
 scalar_t__ nfsd_symlink (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct svc_fh*) ; 
 scalar_t__ nfserr_badtype ; 
 scalar_t__ nfserr_inval ; 
 int /*<<< orphan*/  set_change_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_create(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     union nfsd4_op_u *u)
{
	struct nfsd4_create *create = &u->create;
	struct svc_fh resfh;
	__be32 status;
	dev_t rdev;

	fh_init(&resfh, NFS4_FHSIZE);

	status = fh_verify(rqstp, &cstate->current_fh, S_IFDIR, NFSD_MAY_NOP);
	if (status)
		return status;

	status = check_attr_support(rqstp, cstate, create->cr_bmval,
				    nfsd_attrmask);
	if (status)
		return status;

	current->fs->umask = create->cr_umask;
	switch (create->cr_type) {
	case NF4LNK:
		status = nfsd_symlink(rqstp, &cstate->current_fh,
				      create->cr_name, create->cr_namelen,
				      create->cr_data, &resfh);
		break;

	case NF4BLK:
		status = nfserr_inval;
		rdev = MKDEV(create->cr_specdata1, create->cr_specdata2);
		if (MAJOR(rdev) != create->cr_specdata1 ||
		    MINOR(rdev) != create->cr_specdata2)
			goto out_umask;
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFBLK, rdev, &resfh);
		break;

	case NF4CHR:
		status = nfserr_inval;
		rdev = MKDEV(create->cr_specdata1, create->cr_specdata2);
		if (MAJOR(rdev) != create->cr_specdata1 ||
		    MINOR(rdev) != create->cr_specdata2)
			goto out_umask;
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr,S_IFCHR, rdev, &resfh);
		break;

	case NF4SOCK:
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFSOCK, 0, &resfh);
		break;

	case NF4FIFO:
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFIFO, 0, &resfh);
		break;

	case NF4DIR:
		create->cr_iattr.ia_valid &= ~ATTR_SIZE;
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFDIR, 0, &resfh);
		break;

	default:
		status = nfserr_badtype;
	}

	if (status)
		goto out;

	if (create->cr_label.len)
		nfsd4_security_inode_setsecctx(&resfh, &create->cr_label, create->cr_bmval);

	if (create->cr_acl != NULL)
		do_set_nfs4_acl(rqstp, &resfh, create->cr_acl,
				create->cr_bmval);

	fh_unlock(&cstate->current_fh);
	set_change_info(&create->cr_cinfo, &cstate->current_fh);
	fh_dup2(&cstate->current_fh, &resfh);
out:
	fh_put(&resfh);
out_umask:
	current->fs->umask = 0;
	return status;
}