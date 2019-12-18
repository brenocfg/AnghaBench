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
struct btf_type {int dummy; } ;
typedef  int /*<<< orphan*/  json_writer_t ;
typedef  char __u8 ;
typedef  char __u64 ;
typedef  int __u32 ;
typedef  char __u16 ;

/* Variables and functions */
 scalar_t__ BITS_PER_BYTE_MASKED (int) ; 
 int BTF_INT_BITS (int) ; 
#define  BTF_INT_BOOL 130 
#define  BTF_INT_CHAR 129 
 int BTF_INT_ENCODING (int) ; 
 scalar_t__ BTF_INT_OFFSET (int) ; 
#define  BTF_INT_SIGNED 128 
 int EINVAL ; 
 int /*<<< orphan*/  btf_dumper_int_bits (int,char,void const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btf_int128_print (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  isprint (char) ; 
 int /*<<< orphan*/  jsonw_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jsonw_printf (int /*<<< orphan*/ *,char*,char) ; 

__attribute__((used)) static int btf_dumper_int(const struct btf_type *t, __u8 bit_offset,
			  const void *data, json_writer_t *jw,
			  bool is_plain_text)
{
	__u32 *int_type;
	__u32 nr_bits;

	int_type = (__u32 *)(t + 1);
	nr_bits = BTF_INT_BITS(*int_type);
	/* if this is bit field */
	if (bit_offset || BTF_INT_OFFSET(*int_type) ||
	    BITS_PER_BYTE_MASKED(nr_bits)) {
		btf_dumper_int_bits(*int_type, bit_offset, data, jw,
				    is_plain_text);
		return 0;
	}

	if (nr_bits == 128) {
		btf_int128_print(jw, data, is_plain_text);
		return 0;
	}

	switch (BTF_INT_ENCODING(*int_type)) {
	case 0:
		if (BTF_INT_BITS(*int_type) == 64)
			jsonw_printf(jw, "%llu", *(__u64 *)data);
		else if (BTF_INT_BITS(*int_type) == 32)
			jsonw_printf(jw, "%u", *(__u32 *)data);
		else if (BTF_INT_BITS(*int_type) == 16)
			jsonw_printf(jw, "%hu", *(__u16 *)data);
		else if (BTF_INT_BITS(*int_type) == 8)
			jsonw_printf(jw, "%hhu", *(__u8 *)data);
		else
			btf_dumper_int_bits(*int_type, bit_offset, data, jw,
					    is_plain_text);
		break;
	case BTF_INT_SIGNED:
		if (BTF_INT_BITS(*int_type) == 64)
			jsonw_printf(jw, "%lld", *(long long *)data);
		else if (BTF_INT_BITS(*int_type) == 32)
			jsonw_printf(jw, "%d", *(int *)data);
		else if (BTF_INT_BITS(*int_type) == 16)
			jsonw_printf(jw, "%hd", *(short *)data);
		else if (BTF_INT_BITS(*int_type) == 8)
			jsonw_printf(jw, "%hhd", *(char *)data);
		else
			btf_dumper_int_bits(*int_type, bit_offset, data, jw,
					    is_plain_text);
		break;
	case BTF_INT_CHAR:
		if (isprint(*(char *)data))
			jsonw_printf(jw, "\"%c\"", *(char *)data);
		else
			if (is_plain_text)
				jsonw_printf(jw, "0x%hhx", *(char *)data);
			else
				jsonw_printf(jw, "\"\\u00%02hhx\"",
					     *(char *)data);
		break;
	case BTF_INT_BOOL:
		jsonw_bool(jw, *(int *)data);
		break;
	default:
		/* shouldn't happen */
		return -EINVAL;
	}

	return 0;
}