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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int map_mem (char*,int,int,int) ; 
 int /*<<< orphan*/  scan_rom (char*,char*) ; 
 int /*<<< orphan*/  scan_tree (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
	int rc;

	if (map_mem("/dev/mem", 0, 0xA0000, 1) == 0)
		fprintf(stderr, "PASS: /dev/mem 0x0-0xa0000 is readable\n");
	else
		fprintf(stderr, "FAIL: /dev/mem 0x0-0xa0000 not accessible\n");

	/*
	 * It's not safe to blindly read the VGA frame buffer.  If you know
	 * how to poke the card the right way, it should respond, but it's
	 * not safe in general.  Many machines, e.g., Intel chipsets, cover
	 * up a non-responding card by just returning -1, but others will
	 * report the failure as a machine check.
	 */
	if (map_mem("/dev/mem", 0xA0000, 0x20000, 0) == 0)
		fprintf(stderr, "PASS: /dev/mem 0xa0000-0xc0000 is mappable\n");
	else
		fprintf(stderr, "FAIL: /dev/mem 0xa0000-0xc0000 not accessible\n");

	if (map_mem("/dev/mem", 0xC0000, 0x40000, 1) == 0)
		fprintf(stderr, "PASS: /dev/mem 0xc0000-0x100000 is readable\n");
	else
		fprintf(stderr, "FAIL: /dev/mem 0xc0000-0x100000 not accessible\n");

	/*
	 * Often you can map all the individual pieces above (0-0xA0000,
	 * 0xA0000-0xC0000, and 0xC0000-0x100000), but can't map the whole
	 * thing at once.  This is because the individual pieces use different
	 * attributes, and there's no single attribute supported over the
	 * whole region.
	 */
	rc = map_mem("/dev/mem", 0, 1024*1024, 0);
	if (rc == 0)
		fprintf(stderr, "PASS: /dev/mem 0x0-0x100000 is mappable\n");
	else if (rc > 0)
		fprintf(stderr, "PASS: /dev/mem 0x0-0x100000 not mappable\n");
	else
		fprintf(stderr, "FAIL: /dev/mem 0x0-0x100000 not accessible\n");

	scan_tree("/sys/class/pci_bus", "legacy_mem", 0, 0xA0000, 1);
	scan_tree("/sys/class/pci_bus", "legacy_mem", 0xA0000, 0x20000, 0);
	scan_tree("/sys/class/pci_bus", "legacy_mem", 0xC0000, 0x40000, 1);
	scan_tree("/sys/class/pci_bus", "legacy_mem", 0, 1024*1024, 0);

	scan_rom("/sys/devices", "rom");

	scan_tree("/proc/bus/pci", "??.?", 0, 0xA0000, 1);
	scan_tree("/proc/bus/pci", "??.?", 0xA0000, 0x20000, 0);
	scan_tree("/proc/bus/pci", "??.?", 0xC0000, 0x40000, 1);
	scan_tree("/proc/bus/pci", "??.?", 0, 1024*1024, 0);

	return rc;
}