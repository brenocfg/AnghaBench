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
typedef  int /*<<< orphan*/  tracing_map_cmp_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  tracing_map_cmp_none ; 
 int /*<<< orphan*/  tracing_map_cmp_s16 ; 
 int /*<<< orphan*/  tracing_map_cmp_s32 ; 
 int /*<<< orphan*/  tracing_map_cmp_s64 ; 
 int /*<<< orphan*/  tracing_map_cmp_s8 ; 
 int /*<<< orphan*/  tracing_map_cmp_u16 ; 
 int /*<<< orphan*/  tracing_map_cmp_u32 ; 
 int /*<<< orphan*/  tracing_map_cmp_u64 ; 
 int /*<<< orphan*/  tracing_map_cmp_u8 ; 

tracing_map_cmp_fn_t tracing_map_cmp_num(int field_size,
					 int field_is_signed)
{
	tracing_map_cmp_fn_t fn = tracing_map_cmp_none;

	switch (field_size) {
	case 8:
		if (field_is_signed)
			fn = tracing_map_cmp_s64;
		else
			fn = tracing_map_cmp_u64;
		break;
	case 4:
		if (field_is_signed)
			fn = tracing_map_cmp_s32;
		else
			fn = tracing_map_cmp_u32;
		break;
	case 2:
		if (field_is_signed)
			fn = tracing_map_cmp_s16;
		else
			fn = tracing_map_cmp_u16;
		break;
	case 1:
		if (field_is_signed)
			fn = tracing_map_cmp_s8;
		else
			fn = tracing_map_cmp_u8;
		break;
	}

	return fn;
}