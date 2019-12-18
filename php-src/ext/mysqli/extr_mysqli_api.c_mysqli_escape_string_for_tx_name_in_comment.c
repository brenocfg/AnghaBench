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
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 char* emalloc (scalar_t__) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const* const) ; 

char *
mysqli_escape_string_for_tx_name_in_comment(const char * const name)
{
	char * ret = NULL;
	if (name) {
		zend_bool warned = FALSE;
		const char * p_orig = name;
		char * p_copy;
		p_copy = ret = emalloc(strlen(name) + 1 + 2 + 2 + 1); /* space, open, close, NullS */
		*p_copy++ = ' ';
		*p_copy++ = '/';
		*p_copy++ = '*';
		while (1) {
			register char v = *p_orig;
			if (v == 0) {
				break;
			}
			if ((v >= '0' && v <= '9') ||
				(v >= 'a' && v <= 'z') ||
				(v >= 'A' && v <= 'Z') ||
				v == '-' ||
				v == '_' ||
				v == ' ' ||
				v == '=')
			{
				*p_copy++ = v;
			} else if (warned == FALSE) {
				php_error_docref(NULL, E_WARNING, "Transaction name truncated. Must be only [0-9A-Za-z\\-_=]+");
				warned = TRUE;
			}
			++p_orig;
		}
		*p_copy++ = '*';
		*p_copy++ = '/';
		*p_copy++ = 0;
	}
	return ret;
}