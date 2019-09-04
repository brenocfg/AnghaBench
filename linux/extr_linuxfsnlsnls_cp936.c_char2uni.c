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
typedef  int wchar_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int** page_charset2uni ; 

__attribute__((used)) static int char2uni(const unsigned char *rawstring, int boundlen,
			wchar_t *uni)
{
	unsigned char ch, cl;
	const wchar_t *charset2uni;
	int n;

	if (boundlen <= 0)
		return -ENAMETOOLONG;

	if (boundlen == 1) {
		if (rawstring[0]==0x80) { /* Euro symbol.The only exception with a non-ascii unicode */
			*uni = 0x20ac;
		} else {
			*uni = rawstring[0];
		}
		return 1;
	}

	ch = rawstring[0];
	cl = rawstring[1];

	charset2uni = page_charset2uni[ch];
	if (charset2uni && cl) {
		*uni = charset2uni[cl];
		if (*uni == 0x0000)
			return -EINVAL;
		n = 2;
	} else{
		if (ch==0x80) {/* Euro symbol.The only exception with a non-ascii unicode */
			*uni = 0x20ac;
		} else {
			*uni = ch;
		}
		n = 1;
	}
	return n;
}