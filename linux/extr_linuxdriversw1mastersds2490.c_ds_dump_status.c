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
struct ds_device {int /*<<< orphan*/ * ep; } ;

/* Variables and functions */
 size_t EP_STATUS ; 
 unsigned char RR_APP ; 
 unsigned char RR_CMP ; 
 unsigned char RR_CRC ; 
 unsigned char RR_DETECT ; 
 unsigned char RR_EOS ; 
 unsigned char RR_NRS ; 
 unsigned char RR_RDP ; 
 unsigned char RR_SH ; 
 unsigned char RR_VPP ; 
 int /*<<< orphan*/  ds_print_msg (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void ds_dump_status(struct ds_device *dev, unsigned char *buf, int count)
{
	int i;

	pr_info("0x%x: count=%d, status: ", dev->ep[EP_STATUS], count);
	for (i = 0; i < count; ++i)
		pr_info("%02x ", buf[i]);
	pr_info("\n");

	if (count >= 16) {
		ds_print_msg(buf, "enable flag", 0);
		ds_print_msg(buf, "1-wire speed", 1);
		ds_print_msg(buf, "strong pullup duration", 2);
		ds_print_msg(buf, "programming pulse duration", 3);
		ds_print_msg(buf, "pulldown slew rate control", 4);
		ds_print_msg(buf, "write-1 low time", 5);
		ds_print_msg(buf, "data sample offset/write-0 recovery time",
			6);
		ds_print_msg(buf, "reserved (test register)", 7);
		ds_print_msg(buf, "device status flags", 8);
		ds_print_msg(buf, "communication command byte 1", 9);
		ds_print_msg(buf, "communication command byte 2", 10);
		ds_print_msg(buf, "communication command buffer status", 11);
		ds_print_msg(buf, "1-wire data output buffer status", 12);
		ds_print_msg(buf, "1-wire data input buffer status", 13);
		ds_print_msg(buf, "reserved", 14);
		ds_print_msg(buf, "reserved", 15);
	}
	for (i = 16; i < count; ++i) {
		if (buf[i] == RR_DETECT) {
			ds_print_msg(buf, "new device detect", i);
			continue;
		}
		ds_print_msg(buf, "Result Register Value: ", i);
		if (buf[i] & RR_NRS)
			pr_info("NRS: Reset no presence or ...\n");
		if (buf[i] & RR_SH)
			pr_info("SH: short on reset or set path\n");
		if (buf[i] & RR_APP)
			pr_info("APP: alarming presence on reset\n");
		if (buf[i] & RR_VPP)
			pr_info("VPP: 12V expected not seen\n");
		if (buf[i] & RR_CMP)
			pr_info("CMP: compare error\n");
		if (buf[i] & RR_CRC)
			pr_info("CRC: CRC error detected\n");
		if (buf[i] & RR_RDP)
			pr_info("RDP: redirected page\n");
		if (buf[i] & RR_EOS)
			pr_info("EOS: end of search error\n");
	}
}