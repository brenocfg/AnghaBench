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
 int /*<<< orphan*/  BRCMU_BOARDREV_LEN ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char,int) ; 

char *brcmu_boardrev_str(u32 brev, char *buf)
{
	char c;

	if (brev < 0x100) {
		snprintf(buf, BRCMU_BOARDREV_LEN, "%d.%d",
			 (brev & 0xf0) >> 4, brev & 0xf);
	} else {
		c = (brev & 0xf000) == 0x1000 ? 'P' : 'A';
		snprintf(buf, BRCMU_BOARDREV_LEN, "%c%03x", c, brev & 0xfff);
	}
	return buf;
}