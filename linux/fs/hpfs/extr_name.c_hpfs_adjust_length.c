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

void hpfs_adjust_length(const unsigned char *name, unsigned *len)
{
	if (!*len) return;
	if (*len == 1 && name[0] == '.') return;
	if (*len == 2 && name[0] == '.' && name[1] == '.') return;
	while (*len && (name[*len - 1] == '.' || name[*len - 1] == ' '))
		(*len)--;
}