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
 scalar_t__ kdb_getarea (unsigned char,unsigned long) ; 
 int /*<<< orphan*/  kdb_printf (char*,...) ; 

__attribute__((used)) static int kdb_mdr(unsigned long addr, unsigned int count)
{
	unsigned char c;
	while (count--) {
		if (kdb_getarea(c, addr))
			return 0;
		kdb_printf("%02x", c);
		addr++;
	}
	kdb_printf("\n");
	return 0;
}