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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_BYTE_MASKED (scalar_t__) ; 
 int /*<<< orphan*/  BITS_ROUNDDOWN_BYTES (scalar_t__) ; 
 scalar_t__ BTF_INT_BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ BTF_INT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_bitfield_seq_show (void*,scalar_t__,scalar_t__,struct seq_file*) ; 
 int /*<<< orphan*/  btf_type_int (struct btf_type const*) ; 

__attribute__((used)) static void btf_int_bits_seq_show(const struct btf *btf,
				  const struct btf_type *t,
				  void *data, u8 bits_offset,
				  struct seq_file *m)
{
	u32 int_data = btf_type_int(t);
	u8 nr_bits = BTF_INT_BITS(int_data);
	u8 total_bits_offset;

	/*
	 * bits_offset is at most 7.
	 * BTF_INT_OFFSET() cannot exceed 128 bits.
	 */
	total_bits_offset = bits_offset + BTF_INT_OFFSET(int_data);
	data += BITS_ROUNDDOWN_BYTES(total_bits_offset);
	bits_offset = BITS_PER_BYTE_MASKED(total_bits_offset);
	btf_bitfield_seq_show(data, bits_offset, nr_bits, m);
}