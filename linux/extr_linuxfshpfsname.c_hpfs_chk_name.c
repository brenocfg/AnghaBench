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
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  hpfs_adjust_length (unsigned char const*,unsigned int*) ; 
 scalar_t__ not_allowed_char (unsigned char const) ; 

int hpfs_chk_name(const unsigned char *name, unsigned *len)
{
	int i;
	if (*len > 254) return -ENAMETOOLONG;
	hpfs_adjust_length(name, len);
	if (!*len) return -EINVAL;
	for (i = 0; i < *len; i++) if (not_allowed_char(name[i])) return -EINVAL;
	if (*len == 1) if (name[0] == '.') return -EINVAL;
	if (*len == 2) if (name[0] == '.' && name[1] == '.') return -EINVAL;
	return 0;
}