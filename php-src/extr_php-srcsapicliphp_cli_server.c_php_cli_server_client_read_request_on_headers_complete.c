#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ php_http_parser ;
struct TYPE_6__ {int last_header_element; char* current_header_value; int /*<<< orphan*/  current_header_value_len; } ;
typedef  TYPE_2__ php_cli_server_client ;

/* Variables and functions */
#define  HEADER_FIELD 130 
#define  HEADER_NONE 129 
#define  HEADER_VALUE 128 
 char* pemalloc (int,int) ; 
 int /*<<< orphan*/  php_cli_server_client_save_header (TYPE_2__*) ; 

__attribute__((used)) static int php_cli_server_client_read_request_on_headers_complete(php_http_parser *parser)
{
	php_cli_server_client *client = parser->data;
	switch (client->last_header_element) {
	case HEADER_NONE:
		break;
	case HEADER_FIELD:
		client->current_header_value = pemalloc(1, 1);
		*client->current_header_value = '\0';
		client->current_header_value_len = 0;
		/* break missing intentionally */
	case HEADER_VALUE:
		php_cli_server_client_save_header(client);
		break;
	}
	client->last_header_element = HEADER_NONE;
	return 0;
}