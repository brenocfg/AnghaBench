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

/* Variables and functions */
#define  END 129 
#define  ESC 128 
 int /*<<< orphan*/  ESC_END ; 
 int /*<<< orphan*/  ESC_ESC ; 

__attribute__((used)) static int kiss_esc(unsigned char *s, unsigned char *d, int len)
{
	unsigned char *ptr = d;
	unsigned char c;

	/*
	 * Send an initial END character to flush out any data that may have
	 * accumulated in the receiver due to line noise.
	 */

	*ptr++ = END;

	while (len-- > 0) {
		switch (c = *s++) {
		case END:
			*ptr++ = ESC;
			*ptr++ = ESC_END;
			break;
		case ESC:
			*ptr++ = ESC;
			*ptr++ = ESC_ESC;
			break;
		default:
			*ptr++ = c;
			break;
		}
	}

	*ptr++ = END;

	return ptr - d;
}