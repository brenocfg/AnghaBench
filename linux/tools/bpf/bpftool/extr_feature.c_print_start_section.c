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

/* Variables and functions */
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
print_start_section(const char *json_title, const char *plain_title,
		    const char *define_comment, const char *define_prefix)
{
	if (json_output) {
		jsonw_name(json_wtr, json_title);
		jsonw_start_object(json_wtr);
	} else if (define_prefix) {
		printf("%s\n", define_comment);
	} else {
		printf("%s\n", plain_title);
	}
}