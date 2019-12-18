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
typedef  int uint32_t ;

/* Variables and functions */

void dword_to_bytes(uint32_t dword, uint8_t* bytes) {
    bytes[0] = (dword >> 24) & 0xFF;
    bytes[1] = (dword >> 16) & 0xFF;
    bytes[2] = (dword >> 8) & 0xFF;
    bytes[3] = (dword >> 0) & 0xFF;
}