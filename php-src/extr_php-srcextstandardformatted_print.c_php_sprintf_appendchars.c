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
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_active_function_name () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/ * zend_string_extend (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void
php_sprintf_appendchars(zend_string **buffer, size_t *pos, char *add, size_t len)
{
	if ((*pos + len) >= ZSTR_LEN(*buffer)) {
		size_t nlen = ZSTR_LEN(*buffer);

		PRINTF_DEBUG(("%s(): ereallocing buffer to %d bytes\n", get_active_function_name(), ZSTR_LEN(*buffer)));
		do {
			nlen = nlen << 1;
		} while ((*pos + len) >= nlen);
		*buffer = zend_string_extend(*buffer, nlen, 0);
	}
	PRINTF_DEBUG(("sprintf: appending \"%s\", pos=\n", add, *pos));
	memcpy(ZSTR_VAL(*buffer) + (*pos), add, len);
	*pos += len;
}