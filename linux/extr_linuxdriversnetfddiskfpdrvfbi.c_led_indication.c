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
typedef  int /*<<< orphan*/  u_short ;
struct s_smc {struct s_phy* y; } ;
struct s_phy {struct fddi_mib_p* mib; } ;
struct fddi_mib_p {int dummy; } ;

/* Variables and functions */
 size_t PA ; 
 size_t PB ; 

__attribute__((used)) static void led_indication(struct s_smc *smc, int led_event)
{
	/* use smc->hw.mac_ring_is_up == TRUE 
	 * as indication for Ring Operational
	 */
	u_short			led_state ;
	struct s_phy		*phy ;
	struct fddi_mib_p	*mib_a ;
	struct fddi_mib_p	*mib_b ;

	phy = &smc->y[PA] ;
	mib_a = phy->mib ;
	phy = &smc->y[PB] ;
	mib_b = phy->mib ;

#ifdef	PCI
        led_state = 0 ;
	
	/* Ring up = yellow led OFF*/
	if (led_event == LED_Y_ON) {
		led_state |= LED_MY_ON ;
	}
	else if (led_event == LED_Y_OFF) {
		led_state |= LED_MY_OFF ;
	}
	else {	/* PCM state changed */
		/* Link at Port A/S = green led A ON */
		if (mib_a->fddiPORTPCMState == PC8_ACTIVE) {	
			led_state |= LED_GA_ON ;
		}
		else {
			led_state |= LED_GA_OFF ;
		}
		
		/* Link at Port B = green led B ON */
		if (mib_b->fddiPORTPCMState == PC8_ACTIVE) {
			led_state |= LED_GB_ON ;
		}
		else {
			led_state |= LED_GB_OFF ;
		}
	}

        outp(ADDR(B0_LED), led_state) ;
#endif	/* PCI */

}