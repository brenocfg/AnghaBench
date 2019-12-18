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
struct tep_format_field {struct tep_format_field* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  tep_free_format_field (struct tep_format_field*) ; 

__attribute__((used)) static void free_format_fields(struct tep_format_field *field)
{
	struct tep_format_field *next;

	while (field) {
		next = field->next;
		tep_free_format_field(field);
		field = next;
	}
}