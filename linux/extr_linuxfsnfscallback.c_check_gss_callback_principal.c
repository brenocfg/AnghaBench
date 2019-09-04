#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cr_principal; } ;
struct svc_rqst {TYPE_2__* rq_authop; TYPE_1__ rq_cred; } ;
struct nfs_client {scalar_t__ cl_minorversion; int /*<<< orphan*/  cl_hostname; int /*<<< orphan*/  cl_acceptor; } ;
struct TYPE_4__ {scalar_t__ flavour; } ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_GSS ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

int
check_gss_callback_principal(struct nfs_client *clp, struct svc_rqst *rqstp)
{
	char *p = rqstp->rq_cred.cr_principal;

	if (rqstp->rq_authop->flavour != RPC_AUTH_GSS)
		return 1;

	/* No RPC_AUTH_GSS on NFSv4.1 back channel yet */
	if (clp->cl_minorversion != 0)
		return 0;
	/*
	 * It might just be a normal user principal, in which case
	 * userspace won't bother to tell us the name at all.
	 */
	if (p == NULL)
		return 0;

	/*
	 * Did we get the acceptor from userland during the SETCLIENID
	 * negotiation?
	 */
	if (clp->cl_acceptor)
		return !strcmp(p, clp->cl_acceptor);

	/*
	 * Otherwise try to verify it using the cl_hostname. Note that this
	 * doesn't work if a non-canonical hostname was used in the devname.
	 */

	/* Expect a GSS_C_NT_HOSTBASED_NAME like "nfs@serverhostname" */

	if (memcmp(p, "nfs@", 4) != 0)
		return 0;
	p += 4;
	if (strcmp(p, clp->cl_hostname) != 0)
		return 0;
	return 1;
}