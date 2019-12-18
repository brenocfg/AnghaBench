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
 int /*<<< orphan*/  BMASK ; 
 int /*<<< orphan*/  CMASK ; 
 int /*<<< orphan*/  DDRB ; 
 int /*<<< orphan*/  DDRC ; 
 int /*<<< orphan*/  DDRD ; 
 int /*<<< orphan*/  DMASK ; 
 int /*<<< orphan*/  PORTB ; 
 int /*<<< orphan*/  PORTC ; 
 int /*<<< orphan*/  PORTD ; 

__attribute__((used)) static void unselect_rows(void)
{
    // no need to unselect on mcp23018, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~(BMASK);
    PORTB &= ~(BMASK);
    DDRC  &= ~CMASK;
    PORTC &= ~CMASK;
    DDRD  &= ~DMASK;
    PORTD &= ~DMASK;
}