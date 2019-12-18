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
 int DDRB ; 
 int DDRC ; 
 int DDRD ; 
 int /*<<< orphan*/  KEY_HYS_OFF () ; 
 int /*<<< orphan*/  KEY_UNABLE () ; 
 int PORTC ; 

__attribute__((used)) static inline void KEY_INIT(void)
{
    /* Col */
    DDRB  |=  0x1F;
    /* Key: input with pull-up */
    DDRC  &= ~(1<<6);
    PORTC |=  (1<<6);
    /* Hys */
    DDRC  |=  (1<<7);
    /* Row */
    DDRD  |=  0xF0;

    KEY_UNABLE();
    KEY_HYS_OFF();
}