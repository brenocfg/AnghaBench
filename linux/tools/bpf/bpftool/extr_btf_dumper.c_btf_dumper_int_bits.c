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
typedef  int /*<<< orphan*/  json_writer_t ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int BITS_PER_BYTE_MASKED (int) ; 
 int /*<<< orphan*/  BITS_ROUNDDOWN_BYTES (int) ; 
 int BTF_INT_BITS (int /*<<< orphan*/ ) ; 
 int BTF_INT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_dumper_bitfield (int,int,void const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void btf_dumper_int_bits(__u32 int_type, __u8 bit_offset,
				const void *data, json_writer_t *jw,
				bool is_plain_text)
{
	int nr_bits = BTF_INT_BITS(int_type);
	int total_bits_offset;

	/* bits_offset is at most 7.
	 * BTF_INT_OFFSET() cannot exceed 128 bits.
	 */
	total_bits_offset = bit_offset + BTF_INT_OFFSET(int_type);
	data += BITS_ROUNDDOWN_BYTES(total_bits_offset);
	bit_offset = BITS_PER_BYTE_MASKED(total_bits_offset);
	btf_dumper_bitfield(nr_bits, bit_offset, data, jw,
			    is_plain_text);
}