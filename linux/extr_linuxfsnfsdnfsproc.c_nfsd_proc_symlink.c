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
struct svc_rqst {TYPE_1__ rq_arg; struct nfsd_symlinkargs* rq_argp; } ;
struct svc_fh {int dummy; } ;
struct nfsd_symlinkargs {scalar_t__ tlen; struct svc_fh ffh; int /*<<< orphan*/  tname; int /*<<< orphan*/  flen; int /*<<< orphan*/  fname; int /*<<< orphan*/  first; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_FHSIZE ; 
 scalar_t__ NFS_MAXPATHLEN ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (struct svc_fh*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_symlink (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct svc_fh*) ; 
 int /*<<< orphan*/  nfserr_nametoolong ; 
 int /*<<< orphan*/  nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_fill_symlink_pathname (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __be32
nfsd_proc_symlink(struct svc_rqst *rqstp)
{
	struct nfsd_symlinkargs *argp = rqstp->rq_argp;
	struct svc_fh	newfh;
	__be32		nfserr;

	if (argp->tlen > NFS_MAXPATHLEN)
		return nfserr_nametoolong;

	argp->tname = svc_fill_symlink_pathname(rqstp, &argp->first,
						page_address(rqstp->rq_arg.pages[0]),
						argp->tlen);
	if (IS_ERR(argp->tname))
		return nfserrno(PTR_ERR(argp->tname));

	dprintk("nfsd: SYMLINK  %s %.*s -> %.*s\n",
		SVCFH_fmt(&argp->ffh), argp->flen, argp->fname,
		argp->tlen, argp->tname);

	fh_init(&newfh, NFS_FHSIZE);
	nfserr = nfsd_symlink(rqstp, &argp->ffh, argp->fname, argp->flen,
						 argp->tname, &newfh);

	kfree(argp->tname);
	fh_put(&argp->ffh);
	fh_put(&newfh);
	return nfserr;
}