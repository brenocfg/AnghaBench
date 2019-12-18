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
struct TYPE_2__ {int /*<<< orphan*/  rd_length; int /*<<< orphan*/  rd_offset; int /*<<< orphan*/  rd_fhp; int /*<<< orphan*/  rd_rqstp; scalar_t__ rd_nf; } ;
union nfsd4_op_u {TYPE_1__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd_file_put (scalar_t__) ; 
 int /*<<< orphan*/  trace_nfsd_read_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsd4_read_release(union nfsd4_op_u *u)
{
	if (u->read.rd_nf)
		nfsd_file_put(u->read.rd_nf);
	trace_nfsd_read_done(u->read.rd_rqstp, u->read.rd_fhp,
			     u->read.rd_offset, u->read.rd_length);
}