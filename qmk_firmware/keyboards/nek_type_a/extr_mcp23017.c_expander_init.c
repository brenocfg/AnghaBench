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
 int /*<<< orphan*/  TWI_BITLENGTH_FROM_FREQ (int,int) ; 
 int /*<<< orphan*/  TWI_BIT_PRESCALE_1 ; 
 int /*<<< orphan*/  TWI_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void expander_init(void) {
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 400000));
}