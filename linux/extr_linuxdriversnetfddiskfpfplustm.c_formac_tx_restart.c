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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_CMDREG1 ; 
 int /*<<< orphan*/  FM_ICLLA0 ; 
 int /*<<< orphan*/  FM_ICLLS ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void formac_tx_restart(struct s_smc *smc)
{
	outpw(FM_A(FM_CMDREG1),FM_ICLLS) ;	/* clear s-frame lock */
	outpw(FM_A(FM_CMDREG1),FM_ICLLA0) ;	/* clear a-frame lock */
}