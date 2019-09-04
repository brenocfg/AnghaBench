#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ext_len; int /*<<< orphan*/ * ext; scalar_t__ content_len; int /*<<< orphan*/ * content; int /*<<< orphan*/  headers_original_case; int /*<<< orphan*/  headers; scalar_t__ query_string_len; int /*<<< orphan*/ * query_string; scalar_t__ path_info_len; int /*<<< orphan*/ * path_info; scalar_t__ path_translated_len; int /*<<< orphan*/ * path_translated; scalar_t__ vpath_len; int /*<<< orphan*/ * vpath; scalar_t__ request_uri_len; int /*<<< orphan*/ * request_uri; scalar_t__ protocol_version; } ;
typedef  TYPE_1__ php_cli_server_request ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/ * char_ptr_dtor_p ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int php_cli_server_request_ctor(php_cli_server_request *req) /* {{{ */
{
	req->protocol_version = 0;
	req->request_uri = NULL;
	req->request_uri_len = 0;
	req->vpath = NULL;
	req->vpath_len = 0;
	req->path_translated = NULL;
	req->path_translated_len = 0;
	req->path_info = NULL;
	req->path_info_len = 0;
	req->query_string = NULL;
	req->query_string_len = 0;
	zend_hash_init(&req->headers, 0, NULL, char_ptr_dtor_p, 1);
	zend_hash_init(&req->headers_original_case, 0, NULL, NULL, 1);
	req->content = NULL;
	req->content_len = 0;
	req->ext = NULL;
	req->ext_len = 0;
	return SUCCESS;
}