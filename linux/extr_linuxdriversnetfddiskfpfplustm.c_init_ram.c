#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
struct TYPE_4__ {scalar_t__ rbc_ram_start; int rbc_ram_end; } ;
struct TYPE_6__ {TYPE_1__ fifo; } ;
struct TYPE_5__ {TYPE_3__ fp; } ;
struct s_smc {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_NPP () ; 
 int /*<<< orphan*/  MARW (int) ; 
 int RBC_MEM_SIZE ; 
 int /*<<< orphan*/  write_mdr (struct s_smc*,long) ; 

__attribute__((used)) static void init_ram(struct s_smc *smc)
{
	u_short i ;

	smc->hw.fp.fifo.rbc_ram_start = 0 ;
	smc->hw.fp.fifo.rbc_ram_end =
		smc->hw.fp.fifo.rbc_ram_start + RBC_MEM_SIZE ;
	CHECK_NPP() ;
	MARW(smc->hw.fp.fifo.rbc_ram_start) ;
	for (i = smc->hw.fp.fifo.rbc_ram_start;
		i < (u_short) (smc->hw.fp.fifo.rbc_ram_end-1); i++)
		write_mdr(smc,0L) ;
	/* Erase the last byte too */
	write_mdr(smc,0L) ;
}