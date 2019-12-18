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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static char *decode_mmcr0(u32 value)
{
	static char buf[16];

	buf[0] = '\0';

	if (value & (1 << 31))
		strcat(buf, "FC ");
	if (value & (1 << 26))
		strcat(buf, "PMAE ");
	if (value & (1 << 7))
		strcat(buf, "PMAO ");

	return buf;
}