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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ u8 ;
typedef  enum utf16_endian { ____Placeholder_utf16_endian } utf16_endian ;

/* Variables and functions */
 unsigned long PLANE_SIZE ; 
 unsigned long SURROGATE_BITS ; 
 unsigned long SURROGATE_LOW ; 
 unsigned long SURROGATE_MASK ; 
 unsigned long SURROGATE_PAIR ; 
 unsigned long get_utf16 (int /*<<< orphan*/  const,int) ; 
 int utf32_to_utf8 (unsigned long,scalar_t__*,int) ; 

int utf16s_to_utf8s(const wchar_t *pwcs, int inlen, enum utf16_endian endian,
		u8 *s, int maxout)
{
	u8 *op;
	int size;
	unsigned long u, v;

	op = s;
	while (inlen > 0 && maxout > 0) {
		u = get_utf16(*pwcs, endian);
		if (!u)
			break;
		pwcs++;
		inlen--;
		if (u > 0x7f) {
			if ((u & SURROGATE_MASK) == SURROGATE_PAIR) {
				if (u & SURROGATE_LOW) {
					/* Ignore character and move on */
					continue;
				}
				if (inlen <= 0)
					break;
				v = get_utf16(*pwcs, endian);
				if ((v & SURROGATE_MASK) != SURROGATE_PAIR ||
						!(v & SURROGATE_LOW)) {
					/* Ignore character and move on */
					continue;
				}
				u = PLANE_SIZE + ((u & SURROGATE_BITS) << 10)
						+ (v & SURROGATE_BITS);
				pwcs++;
				inlen--;
			}
			size = utf32_to_utf8(u, op, maxout);
			if (size == -1) {
				/* Ignore character and move on */
			} else {
				op += size;
				maxout -= size;
			}
		} else {
			*op++ = (u8) u;
			maxout--;
		}
	}
	return op - s;
}