#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* content_type; int /*<<< orphan*/ * auth_digest; int /*<<< orphan*/  auth_password; int /*<<< orphan*/  auth_user; int /*<<< orphan*/  content_length; int /*<<< orphan*/  query_string; int /*<<< orphan*/  path_translated; int /*<<< orphan*/  request_uri; int /*<<< orphan*/  proto_num; int /*<<< orphan*/  request_method; } ;
typedef  TYPE_2__ sapi_request_info ;
struct TYPE_6__ {int /*<<< orphan*/  headers; int /*<<< orphan*/  content_len; int /*<<< orphan*/  query_string; int /*<<< orphan*/  path_translated; int /*<<< orphan*/  request_uri; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  request_method; } ;
struct TYPE_8__ {TYPE_1__ request; } ;
typedef  TYPE_3__ php_cli_server_client ;

/* Variables and functions */
 int /*<<< orphan*/  php_http_method_str (int /*<<< orphan*/ ) ; 
 char* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void php_cli_server_client_populate_request_info(const php_cli_server_client *client, sapi_request_info *request_info) /* {{{ */
{
	char *val;

	request_info->request_method = php_http_method_str(client->request.request_method);
	request_info->proto_num = client->request.protocol_version;
	request_info->request_uri = client->request.request_uri;
	request_info->path_translated = client->request.path_translated;
	request_info->query_string = client->request.query_string;
	request_info->content_length = client->request.content_len;
	request_info->auth_user = request_info->auth_password = request_info->auth_digest = NULL;
	if (NULL != (val = zend_hash_str_find_ptr(&client->request.headers, "content-type", sizeof("content-type")-1))) {
		request_info->content_type = val;
	}
}