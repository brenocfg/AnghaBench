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
typedef  int u8 ;
typedef  int /*<<< orphan*/  card_t ;

/* Variables and functions */
 int DSR_EOM ; 
 int /*<<< orphan*/  DSR_TX (int) ; 
 int /*<<< orphan*/  ISR0 ; 
 int /*<<< orphan*/  ISR1 ; 
 int SCA_INTR_DMAC_RX (int) ; 
 int SCA_INTR_DMAC_TX (int) ; 
 int SCA_INTR_MSCI (int) ; 
 int sca_in (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int sca_intr_status(card_t *card)
{
	u8 result = 0;
	u8 isr0 = sca_in(ISR0, card);
	u8 isr1 = sca_in(ISR1, card);

	if (isr1 & 0x03) result |= SCA_INTR_DMAC_RX(0);
	if (isr1 & 0x0C) result |= SCA_INTR_DMAC_TX(0);
	if (isr1 & 0x30) result |= SCA_INTR_DMAC_RX(1);
	if (isr1 & 0xC0) result |= SCA_INTR_DMAC_TX(1);
	if (isr0 & 0x0F) result |= SCA_INTR_MSCI(0);
	if (isr0 & 0xF0) result |= SCA_INTR_MSCI(1);

	if (!(result & SCA_INTR_DMAC_TX(0)))
		if (sca_in(DSR_TX(0), card) & DSR_EOM)
			result |= SCA_INTR_DMAC_TX(0);
	if (!(result & SCA_INTR_DMAC_TX(1)))
		if (sca_in(DSR_TX(1), card) & DSR_EOM)
			result |= SCA_INTR_DMAC_TX(1);

	return result;
}