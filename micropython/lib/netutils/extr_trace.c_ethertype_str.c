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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static const char *ethertype_str(uint16_t type) {
    // A value between 0x0000 - 0x05dc (inclusive) indicates a length, not type
    switch (type) {
        case 0x0800: return "IPv4";
        case 0x0806: return "ARP";
        case 0x86dd: return "IPv6";
        default: return NULL;
    }
}