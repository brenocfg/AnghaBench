#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct svc_fh {int dummy; } ;
struct nfsd3_readdirres {int /*<<< orphan*/  rqstp; struct svc_fh scratch; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS3_FHSIZE ; 
 scalar_t__ compose_entry_fh (struct nfsd3_readdirres*,struct svc_fh*,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__* encode_fh (scalar_t__*,struct svc_fh*) ; 
 scalar_t__* encode_post_op_attr (int /*<<< orphan*/ ,scalar_t__*,struct svc_fh*) ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 scalar_t__ xdr_one ; 

__attribute__((used)) static __be32 *encode_entryplus_baggage(struct nfsd3_readdirres *cd, __be32 *p, const char *name, int namlen, u64 ino)
{
	struct svc_fh	*fh = &cd->scratch;
	__be32 err;

	fh_init(fh, NFS3_FHSIZE);
	err = compose_entry_fh(cd, fh, name, namlen, ino);
	if (err) {
		*p++ = 0;
		*p++ = 0;
		goto out;
	}
	p = encode_post_op_attr(cd->rqstp, p, fh);
	*p++ = xdr_one;			/* yes, a file handle follows */
	p = encode_fh(p, fh);
out:
	fh_put(fh);
	return p;
}