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
struct tep_format_field {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int __tp_field__init_ptr (struct tp_field*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tp_field__init_ptr(struct tp_field *field, struct tep_format_field *format_field)
{
	return __tp_field__init_ptr(field, format_field->offset);
}