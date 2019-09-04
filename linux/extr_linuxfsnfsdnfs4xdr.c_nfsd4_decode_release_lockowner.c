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
struct TYPE_2__ {int len; int /*<<< orphan*/  data; } ;
struct nfsd4_release_lockowner {int /*<<< orphan*/  rl_clientid; TYPE_1__ rl_owner; } ;
struct nfsd4_compoundargs {int minorversion; } ;
typedef  int /*<<< orphan*/  clientid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  COPYMEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READMEM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_notsupp ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  zero_clientid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_decode_release_lockowner(struct nfsd4_compoundargs *argp, struct nfsd4_release_lockowner *rlockowner)
{
	DECODE_HEAD;

	if (argp->minorversion >= 1)
		return nfserr_notsupp;

	READ_BUF(12);
	COPYMEM(&rlockowner->rl_clientid, sizeof(clientid_t));
	rlockowner->rl_owner.len = be32_to_cpup(p++);
	READ_BUF(rlockowner->rl_owner.len);
	READMEM(rlockowner->rl_owner.data, rlockowner->rl_owner.len);

	if (argp->minorversion && !zero_clientid(&rlockowner->rl_clientid))
		return nfserr_inval;
	DECODE_TAIL;
}