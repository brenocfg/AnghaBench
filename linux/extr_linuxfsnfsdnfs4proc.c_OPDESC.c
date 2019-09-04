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
struct nfsd4_operation {int dummy; } ;
struct nfsd4_op {size_t opnum; } ;

/* Variables and functions */
 struct nfsd4_operation const* nfsd4_ops ; 

const struct nfsd4_operation *OPDESC(struct nfsd4_op *op)
{
	return &nfsd4_ops[op->opnum];
}