#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ __u8 ;
struct TYPE_2__ {char const* prefix; scalar_t__ name_index; } ;

/* Variables and functions */
 TYPE_1__* prefix_tbl ; 
 size_t strlen (char const*) ; 

const char *ext4_get_xattr_name_prefix(__u8 name_index,
				       size_t *ret_prefix_len)
{
	int i;

	for (i = 0; prefix_tbl[i].prefix; i++) {
		size_t prefix_len = strlen(prefix_tbl[i].prefix);
		if (prefix_tbl[i].name_index == name_index) {
			if (ret_prefix_len)
				*ret_prefix_len = prefix_len;

			return prefix_tbl[i].prefix;
		}
	}
	if (ret_prefix_len)
		*ret_prefix_len = 0;

	return NULL;
}