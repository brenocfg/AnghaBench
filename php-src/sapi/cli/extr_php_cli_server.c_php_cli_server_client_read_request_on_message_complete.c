#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int http_major; scalar_t__ http_minor; TYPE_3__* data; } ;
typedef  TYPE_2__ php_http_parser ;
struct TYPE_9__ {char* vpath; int vpath_len; char const* ext; int ext_len; scalar_t__ protocol_version; } ;
struct TYPE_8__ {int request_read; TYPE_4__ request; TYPE_1__* server; } ;
typedef  TYPE_3__ php_cli_server_client ;
struct TYPE_6__ {int /*<<< orphan*/  document_root_len; int /*<<< orphan*/  document_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  php_cli_server_request_translate_vpath (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_cli_server_client_read_request_on_message_complete(php_http_parser *parser)
{
	php_cli_server_client *client = parser->data;
	client->request.protocol_version = parser->http_major * 100 + parser->http_minor;
	php_cli_server_request_translate_vpath(&client->request, client->server->document_root, client->server->document_root_len);
	{
		const char *vpath = client->request.vpath, *end = vpath + client->request.vpath_len, *p = end;
		client->request.ext = end;
		client->request.ext_len = 0;
		while (p > vpath) {
			--p;
			if (*p == '.') {
				++p;
				client->request.ext = p;
				client->request.ext_len = end - p;
				break;
			}
		}
	}
	client->request_read = 1;
	return 0;
}