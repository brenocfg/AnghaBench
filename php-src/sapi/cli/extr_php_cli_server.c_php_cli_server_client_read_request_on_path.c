#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* data; } ;
typedef  TYPE_2__ php_http_parser ;
struct TYPE_5__ {char* vpath; size_t vpath_len; } ;
struct TYPE_7__ {TYPE_1__ request; } ;
typedef  TYPE_3__ php_cli_server_client ;

/* Variables and functions */
 int /*<<< orphan*/  normalize_vpath (char**,size_t*,char const*,size_t,int) ; 

__attribute__((used)) static int php_cli_server_client_read_request_on_path(php_http_parser *parser, const char *at, size_t length)
{
	php_cli_server_client *client = parser->data;
	{
		char *vpath;
		size_t vpath_len;
		normalize_vpath(&vpath, &vpath_len, at, length, 1);
		client->request.vpath = vpath;
		client->request.vpath_len = vpath_len;
	}
	return 0;
}