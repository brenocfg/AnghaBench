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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ LSBFIRST ; 
 int /*<<< orphan*/  shiftOut_lsbFirst (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  shiftOut_msbFirst (scalar_t__,scalar_t__,scalar_t__) ; 

void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
        if (bitOrder == LSBFIRST) {
                shiftOut_lsbFirst(dataPin, clockPin, value);
        } else {
                shiftOut_msbFirst(dataPin, clockPin, value);
        }
}