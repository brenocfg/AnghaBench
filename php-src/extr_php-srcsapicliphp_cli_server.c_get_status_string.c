#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  needle ;
struct TYPE_4__ {int member_0; char const* str; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ http_response_status_code_pair ;

/* Variables and functions */
 TYPE_1__* bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_status_map ; 
 int /*<<< orphan*/  http_status_map_len ; 
 int /*<<< orphan*/  status_comp ; 

__attribute__((used)) static const char *get_status_string(int code) /* {{{ */
{
	http_response_status_code_pair needle = {code, NULL},
		*result = NULL;

	result = bsearch(&needle, http_status_map, http_status_map_len, sizeof(needle), status_comp);

	if (result) {
		return result->str;
	}

	/* Returning NULL would require complicating append_http_status_line() to
	 * not segfault in that case, so let's just return a placeholder, since RFC
	 * 2616 requires a reason phrase. This is basically what a lot of other Web
	 * servers do in this case anyway. */
	return "Unknown Status Code";
}