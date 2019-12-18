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
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 scalar_t__ PG (int /*<<< orphan*/ ) ; 
 int PHP_DOUBLE_MAX_LENGTH ; 
 int PHP_JSON_PRESERVE_ZERO_FRACTION ; 
 int /*<<< orphan*/  php_gcvt (double,int,char,char,char*) ; 
 int /*<<< orphan*/  serialize_precision ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static inline void php_json_encode_double(smart_str *buf, double d, int options) /* {{{ */
{
	size_t len;
	char num[PHP_DOUBLE_MAX_LENGTH];

	php_gcvt(d, (int)PG(serialize_precision), '.', 'e', num);
	len = strlen(num);
	if (options & PHP_JSON_PRESERVE_ZERO_FRACTION && strchr(num, '.') == NULL && len < PHP_DOUBLE_MAX_LENGTH - 2) {
		num[len++] = '.';
		num[len++] = '0';
		num[len] = '\0';
	}
	smart_str_appendl(buf, num, len);
}