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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum vrc4171_slotb { ____Placeholder_vrc4171_slotb } vrc4171_slotb ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGURATION1 ; 
 int /*<<< orphan*/  SLOTB_CF ; 
 int /*<<< orphan*/  SLOTB_CONFIG ; 
 int /*<<< orphan*/  SLOTB_FLASHROM ; 
#define  SLOTB_IS_CF 131 
#define  SLOTB_IS_FLASHROM 130 
#define  SLOTB_IS_NONE 129 
#define  SLOTB_IS_PCCARD 128 
 int /*<<< orphan*/  SLOTB_NONE ; 
 int /*<<< orphan*/  SLOTB_PCCARD ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vrc4171_set_multifunction_pin(enum vrc4171_slotb config)
{
	uint16_t config1;

	config1 = inw(CONFIGURATION1);
	config1 &= ~SLOTB_CONFIG;

	switch (config) {
	case SLOTB_IS_NONE:
		config1 |= SLOTB_NONE;
		break;
	case SLOTB_IS_PCCARD:
		config1 |= SLOTB_PCCARD;
		break;
	case SLOTB_IS_CF:
		config1 |= SLOTB_CF;
		break;
	case SLOTB_IS_FLASHROM:
		config1 |= SLOTB_FLASHROM;
		break;
	default:
		break;
	}

	outw(config1, CONFIGURATION1);
}