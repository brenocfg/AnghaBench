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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct seq_file {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 int BITS_PER_BYTE_MASKED (int) ; 
 int BITS_PER_U64 ; 
 int /*<<< orphan*/  BITS_ROUNDDOWN_BYTES (int) ; 
 int BITS_ROUNDUP_BYTES (int) ; 
 int BTF_INT_BITS (int /*<<< orphan*/ ) ; 
 int BTF_INT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_type_int (struct btf_type const*) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static void btf_int_bits_seq_show(const struct btf *btf,
				  const struct btf_type *t,
				  void *data, u8 bits_offset,
				  struct seq_file *m)
{
	u16 left_shift_bits, right_shift_bits;
	u32 int_data = btf_type_int(t);
	u8 nr_bits = BTF_INT_BITS(int_data);
	u8 total_bits_offset;
	u8 nr_copy_bytes;
	u8 nr_copy_bits;
	u64 print_num;

	/*
	 * bits_offset is at most 7.
	 * BTF_INT_OFFSET() cannot exceed 64 bits.
	 */
	total_bits_offset = bits_offset + BTF_INT_OFFSET(int_data);
	data += BITS_ROUNDDOWN_BYTES(total_bits_offset);
	bits_offset = BITS_PER_BYTE_MASKED(total_bits_offset);
	nr_copy_bits = nr_bits + bits_offset;
	nr_copy_bytes = BITS_ROUNDUP_BYTES(nr_copy_bits);

	print_num = 0;
	memcpy(&print_num, data, nr_copy_bytes);

#ifdef __BIG_ENDIAN_BITFIELD
	left_shift_bits = bits_offset;
#else
	left_shift_bits = BITS_PER_U64 - nr_copy_bits;
#endif
	right_shift_bits = BITS_PER_U64 - nr_bits;

	print_num <<= left_shift_bits;
	print_num >>= right_shift_bits;

	seq_printf(m, "0x%llx", print_num);
}