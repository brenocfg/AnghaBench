#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  headers; } ;
struct TYPE_5__ {TYPE_1__ request; } ;
typedef  TYPE_2__ php_cli_server_client ;

/* Variables and functions */
 TYPE_2__* SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_context ; 
 char* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static char *sapi_cli_server_read_cookies(void) /* {{{ */
{
	php_cli_server_client *client = SG(server_context);
	char *val;
	if (NULL == (val = zend_hash_str_find_ptr(&client->request.headers, "cookie", sizeof("cookie")-1))) {
		return NULL;
	}
	return val;
}