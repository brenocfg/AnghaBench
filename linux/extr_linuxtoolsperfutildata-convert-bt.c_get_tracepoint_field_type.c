#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct format_field {unsigned long flags; int size; } ;
struct TYPE_2__ {struct bt_ctf_field_type* u32; struct bt_ctf_field_type* u64; struct bt_ctf_field_type* s32; struct bt_ctf_field_type* s64; struct bt_ctf_field_type* u64_hex; struct bt_ctf_field_type* string; } ;
struct ctf_writer {TYPE_1__ data; } ;
struct bt_ctf_field_type {int dummy; } ;

/* Variables and functions */
 unsigned long FIELD_IS_LONG ; 
 unsigned long FIELD_IS_POINTER ; 
 unsigned long FIELD_IS_SIGNED ; 
 unsigned long FIELD_IS_STRING ; 

__attribute__((used)) static struct bt_ctf_field_type*
get_tracepoint_field_type(struct ctf_writer *cw, struct format_field *field)
{
	unsigned long flags = field->flags;

	if (flags & FIELD_IS_STRING)
		return cw->data.string;

	if (!(flags & FIELD_IS_SIGNED)) {
		/* unsigned long are mostly pointers */
		if (flags & FIELD_IS_LONG || flags & FIELD_IS_POINTER)
			return cw->data.u64_hex;
	}

	if (flags & FIELD_IS_SIGNED) {
		if (field->size == 8)
			return cw->data.s64;
		else
			return cw->data.s32;
	}

	if (field->size == 8)
		return cw->data.u64;
	else
		return cw->data.u32;
}