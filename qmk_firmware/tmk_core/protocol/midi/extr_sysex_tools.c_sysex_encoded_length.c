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
typedef  int uint16_t ;

/* Variables and functions */

uint16_t sysex_encoded_length(uint16_t decoded_length) {
    uint8_t remainder = decoded_length % 7;
    if (remainder)
        return (decoded_length / 7) * 8 + remainder + 1;
    else
        return (decoded_length / 7) * 8;
}