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

__attribute__((used)) static const char *
oui_from_mac(const unsigned char mac[6])
{
    unsigned oui = mac[0]<<16 | mac[1]<<8 | mac[2];
    switch (oui) {
    case 0x0001c0: return "Compulab";
    case 0x000732: return "Aaeon";
    case 0x000c29: return "VMware";
    case 0x001075: return "Seagate";
    case 0x001132: return "Synology";
    case 0x022618: return "Asus";
    case 0x0022b0: return "D-Link";
    case 0x00236c: return "Apple";
    case 0x0016CB: return "Apple";
    case 0x001e06: return "Odroid";
    case 0x001ff3: return "Apple";
    case 0x002590: return "Supermicro";
    case 0x08cc68: return "Cisco";
    case 0x0C9D92: return "Asus";
    case 0x244CE3: return "Amazon";
    case 0x2c27d7: return "HP";
    case 0x3497f6: return "Asus";
    case 0x38f73d: return "Amazon";
    case 0x404a03: return "Zyxel";
    case 0x4C9EFF: return "Zyxel";
    case 0x5855CA: return "Apple";
    case 0x60a44c: return "Asus";
    case 0x6c72e7: return "Apple";
    case 0x9003b7: return "Parrot";
    case 0x94dbc9: return "Azurewave";
    case 0xacbc32: return "Apple";
    case 0xb827eb: return "Raspberry Pi";
    case 0xc05627: return "Belkin";
    case 0xc0c1c0: return "Cisco-Linksys";
    case 0xDCA4CA: return "Apple";
    case 0xe4956e: return "[random]";
    default: return "";
    }
}