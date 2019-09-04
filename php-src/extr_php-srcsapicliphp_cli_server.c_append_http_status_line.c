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
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int /*<<< orphan*/  get_status_string (int) ; 
 int /*<<< orphan*/  smart_str_append_long_ex (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  smart_str_appendc_ex (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  smart_str_appendl_ex (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  smart_str_appends_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void append_http_status_line(smart_str *buffer, int protocol_version, int response_code, int persistent) /* {{{ */
{
	if (!response_code) {
		response_code = 200;
	}
	smart_str_appendl_ex(buffer, "HTTP", 4, persistent);
	smart_str_appendc_ex(buffer, '/', persistent);
	smart_str_append_long_ex(buffer, protocol_version / 100, persistent);
	smart_str_appendc_ex(buffer, '.', persistent);
	smart_str_append_long_ex(buffer, protocol_version % 100, persistent);
	smart_str_appendc_ex(buffer, ' ', persistent);
	smart_str_append_long_ex(buffer, response_code, persistent);
	smart_str_appendc_ex(buffer, ' ', persistent);
	smart_str_appends_ex(buffer, get_status_string(response_code), persistent);
	smart_str_appendl_ex(buffer, "\r\n", 2, persistent);
}