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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ loopback; int /*<<< orphan*/  clock_speed; } ;
struct mgsl_struct {scalar_t__ bus_type; TYPE_1__ params; } ;

/* Variables and functions */
 int BIT12 ; 
 int BIT13 ; 
 scalar_t__ MGSL_BUS_TYPE_ISA ; 
 int /*<<< orphan*/  PCR ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_enable_aux_clock (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_enable_loopback (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_loopback_frame (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_set_sdlc_mode (struct mgsl_struct*) ; 

__attribute__((used)) static void usc_set_sync_mode( struct mgsl_struct *info )
{
	usc_loopback_frame( info );
	usc_set_sdlc_mode( info );

	if (info->bus_type == MGSL_BUS_TYPE_ISA) {
		/* Enable INTEN (Port 6, Bit12) */
		/* This connects the IRQ request signal to the ISA bus */
		usc_OutReg(info, PCR, (u16)((usc_InReg(info, PCR) | BIT13) & ~BIT12));
	}

	usc_enable_aux_clock(info, info->params.clock_speed);

	if (info->params.loopback)
		usc_enable_loopback(info,1);

}