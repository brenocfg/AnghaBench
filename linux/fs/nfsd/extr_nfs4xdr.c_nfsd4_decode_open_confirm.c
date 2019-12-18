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
struct nfsd4_open_confirm {int /*<<< orphan*/  oc_seqid; int /*<<< orphan*/  oc_req_stateid; } ;
struct nfsd4_compoundargs {int minorversion; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfserr_notsupp ; 
 int /*<<< orphan*/  p ; 
 scalar_t__ status ; 

__attribute__((used)) static __be32
nfsd4_decode_open_confirm(struct nfsd4_compoundargs *argp, struct nfsd4_open_confirm *open_conf)
{
	DECODE_HEAD;

	if (argp->minorversion >= 1)
		return nfserr_notsupp;

	status = nfsd4_decode_stateid(argp, &open_conf->oc_req_stateid);
	if (status)
		return status;
	READ_BUF(4);
	open_conf->oc_seqid = be32_to_cpup(p++);

	DECODE_TAIL;
}