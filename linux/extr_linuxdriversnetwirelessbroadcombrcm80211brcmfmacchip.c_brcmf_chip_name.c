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
typedef  int /*<<< orphan*/  uint ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char const*,int,int) ; 

char *brcmf_chip_name(u32 id, u32 rev, char *buf, uint len)
{
	const char *fmt;

	fmt = ((id > 0xa000) || (id < 0x4000)) ? "BCM%d/%u" : "BCM%x/%u";
	snprintf(buf, len, fmt, id, rev);
	return buf;
}