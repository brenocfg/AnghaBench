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
typedef  int /*<<< orphan*/  umode_t ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  __nfsd_open (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int,struct file**) ; 
 int /*<<< orphan*/  validate_process_creds () ; 

__be32
nfsd_open_verified(struct svc_rqst *rqstp, struct svc_fh *fhp, umode_t type,
		int may_flags, struct file **filp)
{
	__be32 err;

	validate_process_creds();
	err = __nfsd_open(rqstp, fhp, type, may_flags, filp);
	validate_process_creds();
	return err;
}