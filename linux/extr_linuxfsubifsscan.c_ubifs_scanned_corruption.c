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
struct ubifs_info {int leb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void*,int,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info const*,char*,int,int,...) ; 

void ubifs_scanned_corruption(const struct ubifs_info *c, int lnum, int offs,
			      void *buf)
{
	int len;

	ubifs_err(c, "corruption at LEB %d:%d", lnum, offs);
	len = c->leb_size - offs;
	if (len > 8192)
		len = 8192;
	ubifs_err(c, "first %d bytes from LEB %d:%d", len, lnum, offs);
	print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 32, 4, buf, len, 1);
}