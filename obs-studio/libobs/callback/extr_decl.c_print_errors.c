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
struct cf_parser {int /*<<< orphan*/  error_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* error_data_buildstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_errors(struct cf_parser *cfp, const char *decl_string)
{
	char *errors = error_data_buildstring(&cfp->error_list);

	if (errors) {
		blog(LOG_WARNING, "Errors/warnings for '%s':\n\n%s",
		     decl_string, errors);

		bfree(errors);
	}
}