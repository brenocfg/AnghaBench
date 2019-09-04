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
typedef  int const uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t get_be32(const uint8_t *buf) {
    return buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
}