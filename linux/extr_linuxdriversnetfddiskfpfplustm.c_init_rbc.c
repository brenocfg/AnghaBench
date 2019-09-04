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
struct TYPE_4__ {scalar_t__ rx2_fifo_start; } ;
struct TYPE_5__ {TYPE_1__ fifo; } ;
struct TYPE_6__ {TYPE_2__ fp; } ;
struct s_smc {TYPE_3__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_EAA1 ; 
 int /*<<< orphan*/  FM_RPXA1 ; 
 int /*<<< orphan*/  FM_SWPXA1 ; 
 int /*<<< orphan*/  FM_WPXA1 ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_recvptr (struct s_smc*) ; 
 int /*<<< orphan*/  set_txptr (struct s_smc*) ; 

__attribute__((used)) static void init_rbc(struct s_smc *smc)
{
	u_short	rbc_ram_addr ;

	/*
	 * set unused pointers or permanent pointers
	 */
	rbc_ram_addr = smc->hw.fp.fifo.rx2_fifo_start - 1 ;

	outpw(FM_A(FM_RPXA1),rbc_ram_addr) ;	/* a1-send pointer */
	outpw(FM_A(FM_WPXA1),rbc_ram_addr) ;
	outpw(FM_A(FM_SWPXA1),rbc_ram_addr) ;
	outpw(FM_A(FM_EAA1),rbc_ram_addr) ;

	set_recvptr(smc) ;
	set_txptr(smc) ;
}