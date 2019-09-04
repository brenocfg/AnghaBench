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
struct tp_field {int offset; int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  tp_field__swapped_u16 ; 
 int /*<<< orphan*/  tp_field__swapped_u32 ; 
 int /*<<< orphan*/  tp_field__swapped_u64 ; 
 int /*<<< orphan*/  tp_field__u16 ; 
 int /*<<< orphan*/  tp_field__u32 ; 
 int /*<<< orphan*/  tp_field__u64 ; 
 int /*<<< orphan*/  tp_field__u8 ; 

__attribute__((used)) static int __tp_field__init_uint(struct tp_field *field, int size, int offset, bool needs_swap)
{
	field->offset = offset;

	switch (size) {
	case 1:
		field->integer = tp_field__u8;
		break;
	case 2:
		field->integer = needs_swap ? tp_field__swapped_u16 : tp_field__u16;
		break;
	case 4:
		field->integer = needs_swap ? tp_field__swapped_u32 : tp_field__u32;
		break;
	case 8:
		field->integer = needs_swap ? tp_field__swapped_u64 : tp_field__u64;
		break;
	default:
		return -1;
	}

	return 0;
}