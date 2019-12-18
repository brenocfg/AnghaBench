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
typedef  int int16_t ;

/* Variables and functions */
 int bmp085_temperature_raw_b5 () ; 

__attribute__((used)) static int16_t bmp085_temperature(void) {
    return (bmp085_temperature_raw_b5() + 8) >> 4;
}