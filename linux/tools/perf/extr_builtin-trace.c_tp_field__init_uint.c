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
struct tp_field {int dummy; } ;
struct tep_format_field {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int __tp_field__init_uint (struct tp_field*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tp_field__init_uint(struct tp_field *field, struct tep_format_field *format_field, bool needs_swap)
{
	return __tp_field__init_uint(field, format_field->size, format_field->offset, needs_swap);
}