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
struct nfsd4_compoundres {int opcnt; TYPE_1__* rqstp; } ;
struct nfsd4_compoundargs {TYPE_2__* ops; } ;
struct TYPE_4__ {scalar_t__ opnum; } ;
struct TYPE_3__ {struct nfsd4_compoundargs* rq_argp; } ;

/* Variables and functions */
 scalar_t__ OP_SEQUENCE ; 

__attribute__((used)) static inline bool nfsd4_is_solo_sequence(struct nfsd4_compoundres *resp)
{
	struct nfsd4_compoundargs *args = resp->rqstp->rq_argp;
	return resp->opcnt == 1 && args->ops[0].opnum == OP_SEQUENCE;
}