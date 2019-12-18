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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int /*<<< orphan*/  headers_original_case; int /*<<< orphan*/  headers; } ;
struct TYPE_5__ {scalar_t__ current_header_value_len; int /*<<< orphan*/ * current_header_value; int /*<<< orphan*/  current_header_name_len; int /*<<< orphan*/ * current_header_name; scalar_t__ current_header_name_allocated; TYPE_1__ request; } ;
typedef  TYPE_2__ php_cli_server_client ;

/* Variables and functions */
 int /*<<< orphan*/  GC_MAKE_PERSISTENT_LOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pefree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_hash_add_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_str_tolower_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zend_string_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void php_cli_server_client_save_header(php_cli_server_client *client)
{
	/* strip off the colon */
	zend_string *orig_header_name = zend_string_init(client->current_header_name, client->current_header_name_len, 1);
	zend_string *lc_header_name = zend_string_alloc(client->current_header_name_len, 1);
	zend_str_tolower_copy(ZSTR_VAL(lc_header_name), client->current_header_name, client->current_header_name_len);
	GC_MAKE_PERSISTENT_LOCAL(orig_header_name);
	GC_MAKE_PERSISTENT_LOCAL(lc_header_name);
	zend_hash_add_ptr(&client->request.headers, lc_header_name, client->current_header_value);
	zend_hash_add_ptr(&client->request.headers_original_case, orig_header_name, client->current_header_value);
	zend_string_release_ex(lc_header_name, 1);
	zend_string_release_ex(orig_header_name, 1);

	if (client->current_header_name_allocated) {
		pefree(client->current_header_name, 1);
		client->current_header_name_allocated = 0;
	}
	client->current_header_name = NULL;
	client->current_header_name_len = 0;
	client->current_header_value = NULL;
	client->current_header_value_len = 0;
}