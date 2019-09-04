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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct btf_type {int /*<<< orphan*/  info; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btf_df_seq_show(const struct btf *btf, const struct btf_type *t,
			    u32 type_id, void *data, u8 bits_offsets,
			    struct seq_file *m)
{
	seq_printf(m, "<unsupported kind:%u>", BTF_INFO_KIND(t->info));
}