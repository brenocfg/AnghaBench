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
typedef  int uint8_t ;
typedef  int int16_t ;

/* Variables and functions */
 int ADCH ; 
 int ADCL ; 
 int ADCSRA ; 
 int ADCSRB ; 
 int ADC_PRESCALER ; 
 int ADEN ; 
 int ADHSM ; 
 int ADMUX ; 
 int ADSC ; 
 int aref ; 

int16_t adc_read(uint8_t mux) {
#if defined(__AVR_AT90USB162__)
    return 0;
#else
    uint8_t low;

    ADCSRA = (1 << ADEN) | ADC_PRESCALER;                // enable ADC
    ADCSRB = (1 << ADHSM) | (mux & 0x20);                // high speed mode
    ADMUX  = aref | (mux & 0x1F);                        // configure mux input
    ADCSRA = (1 << ADEN) | ADC_PRESCALER | (1 << ADSC);  // start the conversion
    while (ADCSRA & (1 << ADSC))
        ;                      // wait for result
    low = ADCL;                // must read LSB first
    return (ADCH << 8) | low;  // must read MSB only once!
#endif
}