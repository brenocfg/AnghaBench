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
struct nfsd4_op {scalar_t__ opnum; } ;
struct TYPE_2__ {int op_flags; } ;

/* Variables and functions */
 TYPE_1__* OPDESC (struct nfsd4_op*) ; 
 int OP_CACHEME ; 
 scalar_t__ OP_ILLEGAL ; 

bool nfsd4_cache_this_op(struct nfsd4_op *op)
{
	if (op->opnum == OP_ILLEGAL)
		return false;
	return OPDESC(op)->op_flags & OP_CACHEME;
}