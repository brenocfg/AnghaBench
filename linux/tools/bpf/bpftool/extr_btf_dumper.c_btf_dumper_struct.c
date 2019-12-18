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
struct btf_type {int /*<<< orphan*/  info; } ;
struct btf_member {int /*<<< orphan*/  type; int /*<<< orphan*/  name_off; scalar_t__ offset; } ;
struct btf_dumper {int /*<<< orphan*/  jw; int /*<<< orphan*/  is_plain_text; int /*<<< orphan*/  btf; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE_MASKED (scalar_t__) ; 
 int BITS_ROUNDDOWN_BYTES (scalar_t__) ; 
 int BTF_INFO_KFLAG (int /*<<< orphan*/ ) ; 
 int BTF_INFO_VLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ BTF_MEMBER_BITFIELD_SIZE (scalar_t__) ; 
 scalar_t__ BTF_MEMBER_BIT_OFFSET (scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  btf__name_by_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btf_dumper_bitfield (scalar_t__,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_dumper_do_type (struct btf_dumper const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btf_dumper_struct(const struct btf_dumper *d, __u32 type_id,
			     const void *data)
{
	const struct btf_type *t;
	struct btf_member *m;
	const void *data_off;
	int kind_flag;
	int ret = 0;
	int i, vlen;

	t = btf__type_by_id(d->btf, type_id);
	if (!t)
		return -EINVAL;

	kind_flag = BTF_INFO_KFLAG(t->info);
	vlen = BTF_INFO_VLEN(t->info);
	jsonw_start_object(d->jw);
	m = (struct btf_member *)(t + 1);

	for (i = 0; i < vlen; i++) {
		__u32 bit_offset = m[i].offset;
		__u32 bitfield_size = 0;

		if (kind_flag) {
			bitfield_size = BTF_MEMBER_BITFIELD_SIZE(bit_offset);
			bit_offset = BTF_MEMBER_BIT_OFFSET(bit_offset);
		}

		jsonw_name(d->jw, btf__name_by_offset(d->btf, m[i].name_off));
		data_off = data + BITS_ROUNDDOWN_BYTES(bit_offset);
		if (bitfield_size) {
			btf_dumper_bitfield(bitfield_size,
					    BITS_PER_BYTE_MASKED(bit_offset),
					    data_off, d->jw, d->is_plain_text);
		} else {
			ret = btf_dumper_do_type(d, m[i].type,
						 BITS_PER_BYTE_MASKED(bit_offset),
						 data_off);
			if (ret)
				break;
		}
	}

	jsonw_end_object(d->jw);

	return ret;
}