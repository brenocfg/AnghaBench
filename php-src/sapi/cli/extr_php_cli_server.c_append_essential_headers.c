#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* val; } ;
typedef  TYPE_2__ zend_string ;
struct timeval {int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  smart_str ;
struct TYPE_7__ {int /*<<< orphan*/  headers; } ;
struct TYPE_9__ {TYPE_1__ request; } ;
typedef  TYPE_3__ php_cli_server_client ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 TYPE_2__* php_format_date (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appendl_ex (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  smart_str_appends_ex (int /*<<< orphan*/ *,char*,int) ; 
 char* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void append_essential_headers(smart_str* buffer, php_cli_server_client *client, int persistent) /* {{{ */
{
	char *val;
	struct timeval tv = {0};

	if (NULL != (val = zend_hash_str_find_ptr(&client->request.headers, "host", sizeof("host")-1))) {
		smart_str_appends_ex(buffer, "Host: ", persistent);
		smart_str_appends_ex(buffer, val, persistent);
		smart_str_appends_ex(buffer, "\r\n", persistent);
	}

	if (!gettimeofday(&tv, NULL)) {
		zend_string *dt = php_format_date("D, d M Y H:i:s", sizeof("D, d M Y H:i:s") - 1, tv.tv_sec, 0);
		smart_str_appends_ex(buffer, "Date: ", persistent);
		smart_str_appends_ex(buffer, dt->val, persistent);
		smart_str_appends_ex(buffer, " GMT\r\n", persistent);
		zend_string_release_ex(dt, 0);
	}

	smart_str_appendl_ex(buffer, "Connection: close\r\n", sizeof("Connection: close\r\n") - 1, persistent);
}