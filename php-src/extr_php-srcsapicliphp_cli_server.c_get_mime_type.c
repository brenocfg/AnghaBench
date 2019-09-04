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
struct TYPE_3__ {int /*<<< orphan*/  extension_mime_types; } ;
typedef  TYPE_1__ php_cli_server ;

/* Variables and functions */
 scalar_t__ zend_hash_str_find_ptr (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static const char *get_mime_type(const php_cli_server *server, const char *ext, size_t ext_len) /* {{{ */
{
	return (const char*)zend_hash_str_find_ptr(&server->extension_mime_types, ext, ext_len);
}