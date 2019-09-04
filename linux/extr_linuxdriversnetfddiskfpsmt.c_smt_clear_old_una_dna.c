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
struct TYPE_4__ {TYPE_1__* m; } ;
struct s_smc {TYPE_2__ mib; } ;
struct TYPE_3__ {void* fddiMACOldDownstreamNbr; void* fddiMACOldUpstreamNbr; } ;

/* Variables and functions */
 size_t MAC0 ; 
 void* SMT_Unknown ; 

__attribute__((used)) static void smt_clear_old_una_dna(struct s_smc *smc)
{
	smc->mib.m[MAC0].fddiMACOldUpstreamNbr = SMT_Unknown ;
	smc->mib.m[MAC0].fddiMACOldDownstreamNbr = SMT_Unknown ;
}