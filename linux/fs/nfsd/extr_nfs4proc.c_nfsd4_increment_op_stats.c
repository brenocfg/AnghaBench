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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * nfs4_opcount; } ;

/* Variables and functions */
 size_t FIRST_NFS4_OP ; 
 size_t LAST_NFS4_OP ; 
 TYPE_1__ nfsdstats ; 

__attribute__((used)) static inline void nfsd4_increment_op_stats(u32 opnum)
{
	if (opnum >= FIRST_NFS4_OP && opnum <= LAST_NFS4_OP)
		nfsdstats.nfs4_opcount[opnum]++;
}