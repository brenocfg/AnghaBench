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
typedef  int /*<<< orphan*/ * hist_field_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hist_field_s16 ; 
 int /*<<< orphan*/ * hist_field_s32 ; 
 int /*<<< orphan*/ * hist_field_s64 ; 
 int /*<<< orphan*/ * hist_field_s8 ; 
 int /*<<< orphan*/ * hist_field_u16 ; 
 int /*<<< orphan*/ * hist_field_u32 ; 
 int /*<<< orphan*/ * hist_field_u64 ; 
 int /*<<< orphan*/ * hist_field_u8 ; 

__attribute__((used)) static hist_field_fn_t select_value_fn(int field_size, int field_is_signed)
{
	hist_field_fn_t fn = NULL;

	switch (field_size) {
	case 8:
		if (field_is_signed)
			fn = hist_field_s64;
		else
			fn = hist_field_u64;
		break;
	case 4:
		if (field_is_signed)
			fn = hist_field_s32;
		else
			fn = hist_field_u32;
		break;
	case 2:
		if (field_is_signed)
			fn = hist_field_s16;
		else
			fn = hist_field_u16;
		break;
	case 1:
		if (field_is_signed)
			fn = hist_field_s8;
		else
			fn = hist_field_u8;
		break;
	}

	return fn;
}