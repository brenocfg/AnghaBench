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
struct TYPE_4__ {int nr_sigs; TYPE_1__* sigs; } ;
struct pnfs_block_volume {int type; TYPE_2__ simple; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  sig_len; int /*<<< orphan*/  sig; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs4_encode_simple(__be32 *p, struct pnfs_block_volume *b)
{
	int i;

	*p++ = cpu_to_be32(1);
	*p++ = cpu_to_be32(b->type);
	*p++ = cpu_to_be32(b->simple.nr_sigs);
	for (i = 0; i < b->simple.nr_sigs; i++) {
		p = xdr_encode_hyper(p, b->simple.sigs[i].offset);
		p = xdr_encode_opaque(p, b->simple.sigs[i].sig,
					 b->simple.sigs[i].sig_len);
	}
}