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
 size_t ALIGN_LEFT ; 
 size_t ALIGN_RIGHT ; 
 int /*<<< orphan*/  E_ERROR ; 
 size_t INT_MAX ; 
 size_t MAX (size_t,size_t) ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  PRINTF_DEBUG (char*) ; 
 int ZEND_SIZE_MAX ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * zend_string_extend (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void
php_sprintf_appendstring(zend_string **buffer, size_t *pos, char *add,
						   size_t min_width, size_t max_width, char padding,
						   size_t alignment, size_t len, int neg, int expprec, int always_sign)
{
	register size_t npad;
	size_t req_size;
	size_t copy_len;
	size_t m_width;

	copy_len = (expprec ? MIN(max_width, len) : len);
	npad = (min_width < copy_len) ? 0 : min_width - copy_len;

	PRINTF_DEBUG(("sprintf: appendstring(%x, %d, %d, \"%s\", %d, '%c', %d)\n",
				  *buffer, *pos, ZSTR_LEN(*buffer), add, min_width, padding, alignment));
	m_width = MAX(min_width, copy_len);

	if(m_width > INT_MAX - *pos - 1) {
		zend_error_noreturn(E_ERROR, "Field width %zd is too long", m_width);
	}

	req_size = *pos + m_width + 1;

	if (req_size > ZSTR_LEN(*buffer)) {
		size_t size = ZSTR_LEN(*buffer);
		while (req_size > size) {
			if (size > ZEND_SIZE_MAX/2) {
				zend_error_noreturn(E_ERROR, "Field width %zd is too long", req_size);
			}
			size <<= 1;
		}
		PRINTF_DEBUG(("sprintf ereallocing buffer to %d bytes\n", size));
		*buffer = zend_string_extend(*buffer, size, 0);
	}
	if (alignment == ALIGN_RIGHT) {
		if ((neg || always_sign) && padding=='0') {
			ZSTR_VAL(*buffer)[(*pos)++] = (neg) ? '-' : '+';
			add++;
			len--;
			copy_len--;
		}
		while (npad-- > 0) {
			ZSTR_VAL(*buffer)[(*pos)++] = padding;
		}
	}
	PRINTF_DEBUG(("sprintf: appending \"%s\"\n", add));
	memcpy(&ZSTR_VAL(*buffer)[*pos], add, copy_len + 1);
	*pos += copy_len;
	if (alignment == ALIGN_LEFT) {
		while (npad--) {
			ZSTR_VAL(*buffer)[(*pos)++] = padding;
		}
	}
}