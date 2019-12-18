#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_JSON_OBJECT_AS_ARRAY ; 
 int php_json_decode_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int php_json_decode(zval *return_value, char *str, int str_len, zend_bool assoc, zend_long depth)
{
	return php_json_decode_ex(return_value, str, str_len, assoc ? PHP_JSON_OBJECT_AS_ARRAY : 0, depth);
}