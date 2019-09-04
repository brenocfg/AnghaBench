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
typedef  int unicode_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int PLANE_SIZE ; 
 int SURROGATE_CHAR_BITS ; 
 int SURROGATE_CHAR_MASK ; 
 int SURROGATE_LOW ; 
 int SURROGATE_MASK ; 
 int SURROGATE_PAIR ; 
 int UNICODE_MAX ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static unicode_t get_utf16_char(const uint8_t *str_i, int str_i_max_len,
				int str_i_idx, int u_ch, unicode_t *ret)
{
	unicode_t c;
	int start_idx = str_i_idx;

	/* Expand OSTA compressed Unicode to Unicode */
	c = str_i[str_i_idx++];
	if (u_ch > 1)
		c = (c << 8) | str_i[str_i_idx++];
	if ((c & SURROGATE_MASK) == SURROGATE_PAIR) {
		unicode_t next;

		/* Trailing surrogate char */
		if (str_i_idx >= str_i_max_len) {
			c = UNICODE_MAX + 1;
			goto out;
		}

		/* Low surrogate must follow the high one... */
		if (c & SURROGATE_LOW) {
			c = UNICODE_MAX + 1;
			goto out;
		}

		WARN_ON_ONCE(u_ch != 2);
		next = str_i[str_i_idx++] << 8;
		next |= str_i[str_i_idx++];
		if ((next & SURROGATE_MASK) != SURROGATE_PAIR ||
		    !(next & SURROGATE_LOW)) {
			c = UNICODE_MAX + 1;
			goto out;
		}

		c = PLANE_SIZE +
		    ((c & SURROGATE_CHAR_MASK) << SURROGATE_CHAR_BITS) +
		    (next & SURROGATE_CHAR_MASK);
	}
out:
	*ret = c;
	return str_i_idx - start_idx;
}