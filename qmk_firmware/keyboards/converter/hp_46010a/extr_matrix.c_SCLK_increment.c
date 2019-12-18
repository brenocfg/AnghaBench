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

/* Variables and functions */
 int /*<<< orphan*/  PORTB ; 
 int /*<<< orphan*/  SCLK ; 
 int /*<<< orphan*/  _delay_us (int) ; 

__attribute__((used)) inline
static
void SCLK_increment(void) {
    PORTB &= ~SCLK ;
    _delay_us( 4 ) ; // make sure the line is stable
    PORTB |= SCLK ;
    _delay_us( 4 ) ;
    
    return ;
}