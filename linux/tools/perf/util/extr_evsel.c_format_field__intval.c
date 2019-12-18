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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tep_format_field {int offset; int size; } ;
struct perf_sample {void* raw_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bswap_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bswap_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bswap_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

u64 format_field__intval(struct tep_format_field *field, struct perf_sample *sample,
			 bool needs_swap)
{
	u64 value;
	void *ptr = sample->raw_data + field->offset;

	switch (field->size) {
	case 1:
		return *(u8 *)ptr;
	case 2:
		value = *(u16 *)ptr;
		break;
	case 4:
		value = *(u32 *)ptr;
		break;
	case 8:
		memcpy(&value, ptr, sizeof(u64));
		break;
	default:
		return 0;
	}

	if (!needs_swap)
		return value;

	switch (field->size) {
	case 2:
		return bswap_16(value);
	case 4:
		return bswap_32(value);
	case 8:
		return bswap_64(value);
	default:
		return 0;
	}

	return 0;
}