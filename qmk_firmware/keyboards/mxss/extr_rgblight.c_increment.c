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
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 

uint8_t increment( uint8_t value, uint8_t step, uint8_t min, uint8_t max ) {
    int16_t new_value = value;
    new_value += step;
    return MIN( MAX( new_value, min ), max );
}