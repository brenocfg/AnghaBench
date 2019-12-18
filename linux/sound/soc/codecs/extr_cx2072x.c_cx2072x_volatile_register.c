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
struct device {int dummy; } ;

/* Variables and functions */
#define  CX2072X_DIGITAL_TEST11 138 
#define  CX2072X_EQ_BAND 137 
#define  CX2072X_EQ_G_COEFF 136 
#define  CX2072X_PORTA_PIN_SENSE 135 
#define  CX2072X_PORTB_PIN_SENSE 134 
#define  CX2072X_PORTD_PIN_SENSE 133 
#define  CX2072X_PORTE_PIN_SENSE 132 
#define  CX2072X_PORTF_PIN_SENSE 131 
#define  CX2072X_REVISION_ID 130 
#define  CX2072X_UM_INTERRUPT_CRTL_E 129 
#define  CX2072X_VENDOR_ID 128 

__attribute__((used)) static bool cx2072x_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CX2072X_VENDOR_ID:
	case CX2072X_REVISION_ID:
	case CX2072X_UM_INTERRUPT_CRTL_E:
	case CX2072X_DIGITAL_TEST11:
	case CX2072X_PORTA_PIN_SENSE:
	case CX2072X_PORTB_PIN_SENSE:
	case CX2072X_PORTD_PIN_SENSE:
	case CX2072X_PORTE_PIN_SENSE:
	case CX2072X_PORTF_PIN_SENSE:
	case CX2072X_EQ_G_COEFF:
	case CX2072X_EQ_BAND:
		return true;
	default:
		return false;
	}
}