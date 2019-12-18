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
struct btf {char const* strings; TYPE_1__* hdr; } ;
typedef  size_t __u32 ;
struct TYPE_2__ {size_t str_len; } ;

/* Variables and functions */

const char *btf__name_by_offset(const struct btf *btf, __u32 offset)
{
	if (offset < btf->hdr->str_len)
		return &btf->strings[offset];
	else
		return NULL;
}