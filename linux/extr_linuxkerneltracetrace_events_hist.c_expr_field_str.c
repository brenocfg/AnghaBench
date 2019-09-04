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
struct hist_field {int flags; } ;

/* Variables and functions */
 int HIST_FIELD_FL_VAR_REF ; 
 char* get_hist_field_flags (struct hist_field*) ; 
 char const* hist_field_name (struct hist_field*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 

__attribute__((used)) static void expr_field_str(struct hist_field *field, char *expr)
{
	if (field->flags & HIST_FIELD_FL_VAR_REF)
		strcat(expr, "$");

	strcat(expr, hist_field_name(field, 0));

	if (field->flags && !(field->flags & HIST_FIELD_FL_VAR_REF)) {
		const char *flags_str = get_hist_field_flags(field);

		if (flags_str) {
			strcat(expr, ".");
			strcat(expr, flags_str);
		}
	}
}