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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void sprom_get_mac(char *mac, const u16 *in)
{
	int i;
	for (i = 0; i < 3; i++) {
		*mac++ = in[i] >> 8;
		*mac++ = in[i];
	}
}