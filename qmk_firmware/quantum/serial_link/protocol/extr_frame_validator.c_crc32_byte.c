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
typedef  size_t uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* poly8_lookup ; 

__attribute__((used)) static uint32_t crc32_byte(uint8_t* p, uint32_t bytelength) {
    uint32_t crc = 0xffffffff;
    while (bytelength-- != 0) crc = poly8_lookup[((uint8_t)crc ^ *(p++))] ^ (crc >> 8);
    // return (~crc); also works
    return (crc ^ 0xffffffff);
}