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
struct nfsd4_op {int /*<<< orphan*/  opnum; } ;
struct TYPE_2__ {int op_flags; } ;

/* Variables and functions */
 TYPE_1__* OPDESC (struct nfsd4_op*) ; 
 int OP_MODIFIES_SOMETHING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nfsd4_op_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void warn_on_nonidempotent_op(struct nfsd4_op *op)
{
	if (OPDESC(op)->op_flags & OP_MODIFIES_SOMETHING) {
		pr_err("unable to encode reply to nonidempotent op %d (%s)\n",
			op->opnum, nfsd4_op_name(op->opnum));
		WARN_ON_ONCE(1);
	}
}