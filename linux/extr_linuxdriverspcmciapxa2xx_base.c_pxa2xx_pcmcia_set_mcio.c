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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCIO (int) ; 
 int MCXX_ASST_MASK ; 
 int MCXX_ASST_SHIFT ; 
 int MCXX_HOLD_MASK ; 
 int MCXX_HOLD_SHIFT ; 
 int MCXX_SETUP_MASK ; 
 int MCXX_SETUP_SHIFT ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int pxa2xx_mcxx_asst (int,int) ; 
 int pxa2xx_mcxx_hold (int,int) ; 
 int pxa2xx_mcxx_setup (int,int) ; 

__attribute__((used)) static int pxa2xx_pcmcia_set_mcio( int sock, int speed, int clock )
{
	uint32_t val;

	val = ((pxa2xx_mcxx_setup(speed, clock)
		& MCXX_SETUP_MASK) << MCXX_SETUP_SHIFT)
		| ((pxa2xx_mcxx_asst(speed, clock)
		& MCXX_ASST_MASK) << MCXX_ASST_SHIFT)
		| ((pxa2xx_mcxx_hold(speed, clock)
		& MCXX_HOLD_MASK) << MCXX_HOLD_SHIFT);

	__raw_writel(val, MCIO(sock));

	return 0;
}