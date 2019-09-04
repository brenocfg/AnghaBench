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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  PRINTF_DEBUG (char*) ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_active_function_name () ; 
 int /*<<< orphan*/ * zend_string_extend (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void
php_sprintf_appendchar(zend_string **buffer, size_t *pos, char add)
{
	if ((*pos + 1) >= ZSTR_LEN(*buffer)) {
		PRINTF_DEBUG(("%s(): ereallocing buffer to %d bytes\n", get_active_function_name(), ZSTR_LEN(*buffer)));
		*buffer = zend_string_extend(*buffer, ZSTR_LEN(*buffer) << 1, 0);
	}
	PRINTF_DEBUG(("sprintf: appending '%c', pos=\n", add, *pos));
	ZSTR_VAL(*buffer)[(*pos)++] = add;
}