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
typedef  int uint8_t ;
typedef  char uchar ;
typedef  int int8_t ;

/* Variables and functions */
#define  S_F 133 
#define  S_I 132 
#define  S_N 131 
#define  S_Z 130 
 char TOUPPER (char const) ; 
#define  VCMP 129 
#define  VLEN 128 
 scalar_t__ xisdigit (char const) ; 

__attribute__((used)) static int xstrverscasecmp(const char * const s1, const char * const s2)
{
	const uchar *p1 = (const uchar *)s1;
	const uchar *p2 = (const uchar *)s2;
	int state, diff;
	uchar c1, c2;

	/*
	 * Symbol(s)    0       [1-9]   others
	 * Transition   (10) 0  (01) d  (00) x
	 */
	static const uint8_t next_state[] = {
		/* state    x    d    0  */
		/* S_N */  S_N, S_I, S_Z,
		/* S_I */  S_N, S_I, S_I,
		/* S_F */  S_N, S_F, S_F,
		/* S_Z */  S_N, S_F, S_Z
	};

	static const int8_t result_type[] __attribute__ ((aligned)) = {
		/* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

		/* S_N */  VCMP, VCMP, VCMP, VCMP, VLEN, VCMP, VCMP, VCMP, VCMP,
		/* S_I */  VCMP,   -1,   -1,    1, VLEN, VLEN,    1, VLEN, VLEN,
		/* S_F */  VCMP, VCMP, VCMP, VCMP, VCMP, VCMP, VCMP, VCMP, VCMP,
		/* S_Z */  VCMP,    1,    1,   -1, VCMP, VCMP,   -1, VCMP, VCMP
	};

	if (p1 == p2)
		return 0;

	c1 = TOUPPER(*p1);
	++p1;
	c2 = TOUPPER(*p2);
	++p2;

	/* Hint: '0' is a digit too.  */
	state = S_N + ((c1 == '0') + (xisdigit(c1) != 0));

	while ((diff = c1 - c2) == 0) {
		if (c1 == '\0')
			return diff;

		state = next_state[state];
		c1 = TOUPPER(*p1);
		++p1;
		c2 = TOUPPER(*p2);
		++p2;
		state += (c1 == '0') + (xisdigit(c1) != 0);
	}

	state = result_type[state * 3 + (((c2 == '0') + (xisdigit(c2) != 0)))];

	switch (state) {
	case VCMP:
		return diff;
	case VLEN:
		while (xisdigit(*p1++))
			if (!xisdigit(*p2++))
				return 1;
		return xisdigit(*p2) ? -1 : diff;
	default:
		return state;
	}
}