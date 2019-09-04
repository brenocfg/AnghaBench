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
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,void*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void*,int,int) ; 

void
cifs_dump_mem(char *label, void *data, int length)
{
	pr_debug("%s: dump of %d bytes of data at 0x%p\n", label, length, data);
	print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 16, 4,
		       data, length, true);
}