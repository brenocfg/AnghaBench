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
struct tep_print_flag_sym {struct tep_print_flag_sym* next; int /*<<< orphan*/  str; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  define_flag_value (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void define_flag_values(struct tep_print_flag_sym *field,
			       const char *ev_name,
			       const char *field_name)
{
	define_flag_value(ev_name, field_name, field->value, field->str);
	if (field->next)
		define_flag_values(field->next, ev_name, field_name);
}