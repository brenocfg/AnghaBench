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
 char* cmd_to_page (char const*) ; 
 scalar_t__ get_html_page_path (char**,char const*) ; 
 int /*<<< orphan*/  open_html (char*) ; 

__attribute__((used)) static int show_html_page(const char *perf_cmd)
{
	const char *page = cmd_to_page(perf_cmd);
	char *page_path; /* it leaks but we exec bellow */

	if (get_html_page_path(&page_path, page) < 0)
		return -1;

	open_html(page_path);

	return 0;
}