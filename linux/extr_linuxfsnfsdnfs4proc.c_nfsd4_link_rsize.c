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
typedef  int u32 ;
struct svc_rqst {int dummy; } ;
struct nfsd4_op {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int op_encode_change_info_maxsz ; 
 int op_encode_hdr_size ; 

__attribute__((used)) static inline u32 nfsd4_link_rsize(struct svc_rqst *rqstp, struct nfsd4_op *op)
{
	return (op_encode_hdr_size + op_encode_change_info_maxsz)
		* sizeof(__be32);
}