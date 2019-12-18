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
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_post_attr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * encode_fattr3 (struct svc_rqst*,int /*<<< orphan*/ *,struct svc_fh*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_one ; 

__attribute__((used)) static __be32 *
encode_saved_post_attr(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp)
{
	/* Attributes to follow */
	*p++ = xdr_one;
	return encode_fattr3(rqstp, p, fhp, &fhp->fh_post_attr);
}