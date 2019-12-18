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
struct btf_ext {int /*<<< orphan*/  line_info; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int btf_ext_reloc_info (struct btf const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 

int btf_ext__reloc_line_info(const struct btf *btf,
			     const struct btf_ext *btf_ext,
			     const char *sec_name, __u32 insns_cnt,
			     void **line_info, __u32 *cnt)
{
	return btf_ext_reloc_info(btf, &btf_ext->line_info, sec_name,
				  insns_cnt, line_info, cnt);
}