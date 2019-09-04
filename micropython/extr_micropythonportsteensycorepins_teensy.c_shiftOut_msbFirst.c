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

/* Variables and functions */
 int HIGH ; 
 int LOW ; 
 int /*<<< orphan*/  digitalWrite (int,int) ; 

void shiftOut_msbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value)
{
        uint8_t mask;
        for (mask=0x80; mask; mask >>= 1) {
                digitalWrite(dataPin, value & mask);
                digitalWrite(clockPin, HIGH);
                digitalWrite(clockPin, LOW);
        }
}