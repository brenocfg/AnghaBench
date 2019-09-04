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
typedef  size_t u32 ;
struct TYPE_2__ {size_t str_len; } ;
struct btf {char const* strings; TYPE_1__ hdr; } ;

/* Variables and functions */

__attribute__((used)) static const char *btf_name_by_offset(const struct btf *btf, u32 offset)
{
	if (!offset)
		return "(anon)";
	else if (offset < btf->hdr.str_len)
		return &btf->strings[offset];
	else
		return "(invalid-name-offset)";
}