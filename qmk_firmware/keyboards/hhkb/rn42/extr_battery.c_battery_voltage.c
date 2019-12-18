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
typedef  int volatile uint16_t ;

/* Variables and functions */
 int ADC ; 
 int ADCSRA ; 
 int ADEN ; 
 int ADSC ; 
 int volatile BATTERY_ADC_OFFSET ; 
 int volatile BATTERY_ADC_RESOLUTION ; 
 int DDRF ; 
 int PORTF ; 
 int /*<<< orphan*/  _delay_ms (int) ; 

uint16_t battery_voltage(void)
{
    // ADC disable voltate divider(PF4)
    DDRF  |=  (1<<4);
    PORTF |=  (1<<4);

    volatile uint16_t bat;
    ADCSRA |= (1<<ADEN);
    _delay_ms(1);   // wait for charging S/H capacitance

    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC)) ;
    bat = ADC;

    ADCSRA &= ~(1<<ADEN);

    // ADC disable voltate divider(PF4)
    DDRF  |=  (1<<4);
    PORTF &= ~(1<<4);

    return (bat - BATTERY_ADC_OFFSET) * BATTERY_ADC_RESOLUTION;
}