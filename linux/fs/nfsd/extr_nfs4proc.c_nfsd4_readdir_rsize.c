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
typedef  int u32 ;
struct svc_rqst {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rd_maxcount; } ;
struct TYPE_4__ {TYPE_1__ readdir; } ;
struct nfsd4_op {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int XDR_QUADLEN (int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int op_encode_hdr_size ; 
 int op_encode_verifier_maxsz ; 
 int svc_max_payload (struct svc_rqst*) ; 

__attribute__((used)) static inline u32 nfsd4_readdir_rsize(struct svc_rqst *rqstp, struct nfsd4_op *op)
{
	u32 maxcount = 0, rlen = 0;

	maxcount = svc_max_payload(rqstp);
	rlen = min(op->u.readdir.rd_maxcount, maxcount);

	return (op_encode_hdr_size + op_encode_verifier_maxsz +
		XDR_QUADLEN(rlen)) * sizeof(__be32);
}