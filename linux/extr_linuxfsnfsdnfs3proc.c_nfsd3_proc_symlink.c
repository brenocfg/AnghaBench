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
struct TYPE_2__ {int /*<<< orphan*/ * pages; } ;
struct svc_rqst {TYPE_1__ rq_arg; struct nfsd3_diropres* rq_resp; struct nfsd3_symlinkargs* rq_argp; } ;
struct nfsd3_symlinkargs {scalar_t__ tlen; int /*<<< orphan*/  tname; int /*<<< orphan*/  flen; int /*<<< orphan*/  fname; int /*<<< orphan*/  ffh; int /*<<< orphan*/  first; } ;
struct nfsd3_diropres {int /*<<< orphan*/  fh; int /*<<< orphan*/  dirfh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS3_FHSIZE ; 
 scalar_t__ NFS3_MAXPATHLEN ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_symlink (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_nametoolong ; 
 int /*<<< orphan*/  nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_fill_symlink_pathname (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __be32
nfsd3_proc_symlink(struct svc_rqst *rqstp)
{
	struct nfsd3_symlinkargs *argp = rqstp->rq_argp;
	struct nfsd3_diropres *resp = rqstp->rq_resp;
	__be32	nfserr;

	if (argp->tlen == 0)
		RETURN_STATUS(nfserr_inval);
	if (argp->tlen > NFS3_MAXPATHLEN)
		RETURN_STATUS(nfserr_nametoolong);

	argp->tname = svc_fill_symlink_pathname(rqstp, &argp->first,
						page_address(rqstp->rq_arg.pages[0]),
						argp->tlen);
	if (IS_ERR(argp->tname))
		RETURN_STATUS(nfserrno(PTR_ERR(argp->tname)));

	dprintk("nfsd: SYMLINK(3)  %s %.*s -> %.*s\n",
				SVCFH_fmt(&argp->ffh),
				argp->flen, argp->fname,
				argp->tlen, argp->tname);

	fh_copy(&resp->dirfh, &argp->ffh);
	fh_init(&resp->fh, NFS3_FHSIZE);
	nfserr = nfsd_symlink(rqstp, &resp->dirfh, argp->fname, argp->flen,
						   argp->tname, &resp->fh);
	kfree(argp->tname);
	RETURN_STATUS(nfserr);
}