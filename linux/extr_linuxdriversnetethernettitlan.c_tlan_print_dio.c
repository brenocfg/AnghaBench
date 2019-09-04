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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  tlan_dio_read32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tlan_print_dio(u16 io_base)
{
	u32 data0, data1;
	int	i;

	pr_info("Contents of internal registers for io base 0x%04hx\n",
		io_base);
	pr_info("Off.  +0        +4\n");
	for (i = 0; i < 0x4C; i += 8) {
		data0 = tlan_dio_read32(io_base, i);
		data1 = tlan_dio_read32(io_base, i + 0x4);
		pr_info("0x%02x  0x%08x 0x%08x\n", i, data0, data1);
	}

}