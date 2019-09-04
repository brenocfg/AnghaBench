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
struct TYPE_3__ {size_t len; int* val; } ;
typedef  TYPE_1__ zend_string ;
typedef  int /*<<< orphan*/  zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  SUCCESS ; 

__attribute__((used)) static zend_bool php_mail_build_headers_check_field_name(zend_string *key)
{
	size_t len = 0;

	/* https://tools.ietf.org/html/rfc2822#section-2.2 */
	while (len < key->len) {
		if (*(key->val+len) < 33 || *(key->val+len) > 126 || *(key->val+len) == ':') {
			return FAILURE;
		}
		len++;
	}
	return SUCCESS;
}