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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct seq_file {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf {int dummy; } ;
typedef  int s8 ;
typedef  int s64 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ BITS_PER_BYTE_MASKED (int) ; 
 int BTF_INT_BITS (int) ; 
 int BTF_INT_ENCODING (int) ; 
 scalar_t__ BTF_INT_OFFSET (int) ; 
 int BTF_INT_SIGNED ; 
 int /*<<< orphan*/  btf_int128_print (struct seq_file*,void*) ; 
 int /*<<< orphan*/  btf_int_bits_seq_show (struct btf const*,struct btf_type const*,void*,int,struct seq_file*) ; 
 int btf_type_int (struct btf_type const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static void btf_int_seq_show(const struct btf *btf, const struct btf_type *t,
			     u32 type_id, void *data, u8 bits_offset,
			     struct seq_file *m)
{
	u32 int_data = btf_type_int(t);
	u8 encoding = BTF_INT_ENCODING(int_data);
	bool sign = encoding & BTF_INT_SIGNED;
	u8 nr_bits = BTF_INT_BITS(int_data);

	if (bits_offset || BTF_INT_OFFSET(int_data) ||
	    BITS_PER_BYTE_MASKED(nr_bits)) {
		btf_int_bits_seq_show(btf, t, data, bits_offset, m);
		return;
	}

	switch (nr_bits) {
	case 128:
		btf_int128_print(m, data);
		break;
	case 64:
		if (sign)
			seq_printf(m, "%lld", *(s64 *)data);
		else
			seq_printf(m, "%llu", *(u64 *)data);
		break;
	case 32:
		if (sign)
			seq_printf(m, "%d", *(s32 *)data);
		else
			seq_printf(m, "%u", *(u32 *)data);
		break;
	case 16:
		if (sign)
			seq_printf(m, "%d", *(s16 *)data);
		else
			seq_printf(m, "%u", *(u16 *)data);
		break;
	case 8:
		if (sign)
			seq_printf(m, "%d", *(s8 *)data);
		else
			seq_printf(m, "%u", *(u8 *)data);
		break;
	default:
		btf_int_bits_seq_show(btf, t, data, bits_offset, m);
	}
}