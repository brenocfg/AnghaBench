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
struct wl3501_card {int base_addr; int* mac_addr; void** version; void* reg_domain; } ;

/* Variables and functions */
 int WL3501_BSS_FPAGE0 ; 
 int WL3501_BSS_FPAGE3 ; 
 int /*<<< orphan*/  WL3501_BSS_SPAGE0 ; 
 scalar_t__ WL3501_NIC_BSS ; 
 scalar_t__ WL3501_NIC_IODPA ; 
 scalar_t__ WL3501_NIC_LMAH ; 
 scalar_t__ WL3501_NIC_LMAL ; 
 int /*<<< orphan*/  WL3501_NOPLOOP (int) ; 
 void* inb (scalar_t__) ; 
 int /*<<< orphan*/  wl3501_outb (int,scalar_t__) ; 
 int /*<<< orphan*/  wl3501_switch_page (struct wl3501_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl3501_get_flash_mac_addr(struct wl3501_card *this)
{
	int base_addr = this->base_addr;

	/* get MAC addr */
	wl3501_outb(WL3501_BSS_FPAGE3, base_addr + WL3501_NIC_BSS); /* BSS */
	wl3501_outb(0x00, base_addr + WL3501_NIC_LMAL);	/* LMAL */
	wl3501_outb(0x40, base_addr + WL3501_NIC_LMAH);	/* LMAH */

	/* wait for reading EEPROM */
	WL3501_NOPLOOP(100);
	this->mac_addr[0] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[1] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[2] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[3] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[4] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[5] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->reg_domain = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	wl3501_outb(WL3501_BSS_FPAGE0, base_addr + WL3501_NIC_BSS);
	wl3501_outb(0x04, base_addr + WL3501_NIC_LMAL);
	wl3501_outb(0x40, base_addr + WL3501_NIC_LMAH);
	WL3501_NOPLOOP(100);
	this->version[0] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->version[1] = inb(base_addr + WL3501_NIC_IODPA);
	/* switch to SRAM Page 0 (for safety) */
	wl3501_switch_page(this, WL3501_BSS_SPAGE0);

	/* The MAC addr should be 00:60:... */
	return this->mac_addr[0] == 0x00 && this->mac_addr[1] == 0x60;
}