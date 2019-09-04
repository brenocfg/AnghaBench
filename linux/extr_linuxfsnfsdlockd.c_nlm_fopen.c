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
struct svc_rqst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fh_base; int /*<<< orphan*/  fh_size; } ;
struct svc_fh {int /*<<< orphan*/ * fh_export; TYPE_1__ fh_handle; } ;
struct nfs_fh {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct file {int dummy; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_MAY_LOCK ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  nfs_ok 130 
 int nfsd_open (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
#define  nfserr_dropit 129 
#define  nfserr_stale 128 
 int nlm_drop_reply ; 
 int nlm_failed ; 
 int nlm_stale_fh ; 

__attribute__((used)) static __be32
nlm_fopen(struct svc_rqst *rqstp, struct nfs_fh *f, struct file **filp)
{
	__be32		nfserr;
	struct svc_fh	fh;

	/* must initialize before using! but maxsize doesn't matter */
	fh_init(&fh,0);
	fh.fh_handle.fh_size = f->size;
	memcpy((char*)&fh.fh_handle.fh_base, f->data, f->size);
	fh.fh_export = NULL;

	nfserr = nfsd_open(rqstp, &fh, S_IFREG, NFSD_MAY_LOCK, filp);
	fh_put(&fh);
 	/* We return nlm error codes as nlm doesn't know
	 * about nfsd, but nfsd does know about nlm..
	 */
	switch (nfserr) {
	case nfs_ok:
		return 0;
	case nfserr_dropit:
		return nlm_drop_reply;
	case nfserr_stale:
		return nlm_stale_fh;
	default:
		return nlm_failed;
	}
}