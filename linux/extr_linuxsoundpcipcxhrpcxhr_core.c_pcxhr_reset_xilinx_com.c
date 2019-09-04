#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcxhr_mgr {int dummy; } ;

/* Variables and functions */
 int PCXHR_CHIPSC_INIT_VALUE ; 
 int PCXHR_CHIPSC_RESET_XILINX ; 
 int /*<<< orphan*/  PCXHR_OUTPL (struct pcxhr_mgr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCXHR_PLX_CHIPSC ; 

void pcxhr_reset_xilinx_com(struct pcxhr_mgr *mgr)
{
	/* reset second xilinx */
	PCXHR_OUTPL(mgr, PCXHR_PLX_CHIPSC,
		    PCXHR_CHIPSC_INIT_VALUE & ~PCXHR_CHIPSC_RESET_XILINX);
}