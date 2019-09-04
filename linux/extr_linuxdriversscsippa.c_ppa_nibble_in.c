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
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 

__attribute__((used)) static int ppa_nibble_in(unsigned short base, char *buffer, int len)
{
	for (; len; len--) {
		unsigned char h;

		w_ctr(base, 0x4);
		h = r_str(base) & 0xf0;
		w_ctr(base, 0x6);
		*buffer++ = h | ((r_str(base) & 0xf0) >> 4);
	}
	return 1;		/* All went well - we hope! */
}