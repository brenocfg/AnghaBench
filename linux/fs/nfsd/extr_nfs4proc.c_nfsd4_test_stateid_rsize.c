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
struct TYPE_3__ {int ts_num_ids; } ;
struct TYPE_4__ {TYPE_1__ test_stateid; } ;
struct nfsd4_op {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int op_encode_hdr_size ; 

__attribute__((used)) static inline u32 nfsd4_test_stateid_rsize(struct svc_rqst *rqstp, struct nfsd4_op *op)
{
	return (op_encode_hdr_size + 1 + op->u.test_stateid.ts_num_ids)
		* sizeof(__be32);
}