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
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  SNIC_INFO (char*,char*,int) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,char*,int) ; 

void
snic_hex_dump(char *pfx, char *data, int len)
{
	SNIC_INFO("%s Dumping Data of Len = %d\n", pfx, len);
	print_hex_dump_bytes(pfx, DUMP_PREFIX_NONE, data, len);
}