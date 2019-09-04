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
struct ftrace_event_field {scalar_t__ size; scalar_t__ is_signed; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool compatible_field(struct ftrace_event_field *field,
			     struct ftrace_event_field *test_field)
{
	if (field == test_field)
		return true;
	if (field == NULL || test_field == NULL)
		return false;
	if (strcmp(field->name, test_field->name) != 0)
		return false;
	if (strcmp(field->type, test_field->type) != 0)
		return false;
	if (field->size != test_field->size)
		return false;
	if (field->is_signed != test_field->is_signed)
		return false;

	return true;
}