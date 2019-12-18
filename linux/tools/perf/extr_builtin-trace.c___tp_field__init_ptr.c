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
struct tp_field {int offset; int /*<<< orphan*/  pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  tp_field__ptr ; 

__attribute__((used)) static int __tp_field__init_ptr(struct tp_field *field, int offset)
{
	field->offset = offset;
	field->pointer = tp_field__ptr;
	return 0;
}