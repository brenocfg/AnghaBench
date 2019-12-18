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
struct nfsd4_setclientid_confirm {int /*<<< orphan*/  sc_confirm; int /*<<< orphan*/  sc_clientid; } ;
struct nfsd4_compoundargs {int minorversion; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  COPYMEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int NFS4_VERIFIER_SIZE ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  nfserr_notsupp ; 

__attribute__((used)) static __be32
nfsd4_decode_setclientid_confirm(struct nfsd4_compoundargs *argp, struct nfsd4_setclientid_confirm *scd_c)
{
	DECODE_HEAD;

	if (argp->minorversion >= 1)
		return nfserr_notsupp;

	READ_BUF(8 + NFS4_VERIFIER_SIZE);
	COPYMEM(&scd_c->sc_clientid, 8);
	COPYMEM(&scd_c->sc_confirm, NFS4_VERIFIER_SIZE);

	DECODE_TAIL;
}