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
typedef  int ut8 ;
typedef  int ssize_t ;

/* Variables and functions */
 int r_cons_controlz (int) ; 
 int r_cons_readchar () ; 
 int r_line_readchar_win (int*,int) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int t ; 

__attribute__((used)) static int r_line_readchar_utf8(ut8 *s, int slen) {
#if __WINDOWS__
	return r_line_readchar_win (s, slen);
#else
	// TODO: add support for w32
	ssize_t len, i;
	if (slen < 1) {
		return 0;
	}
	int ch = r_cons_readchar ();
	if (ch == -1) {
		return -1;
	}
	*s = ch;
#if 0
	if ((t = read (0, s, 1)) != 1) {
		return t;
	}
#endif
	*s = r_cons_controlz (*s);
	if (*s < 0x80) {
		len = 1;
	} else if ((s[0] & 0xe0) == 0xc0) {
		len = 2;
	} else if ((s[0] & 0xf0) == 0xe0) {
		len = 3;
	} else if ((s[0] & 0xf8) == 0xf0) {
		len = 4;
	} else {
		return -1;
	}
	if (len > slen) {
		return -1;
	}
	for (i = 1; i < len; i++) {
		int ch = r_cons_readchar ();
		if (ch != -1) {
			s[i] = ch;
		}
		if ((s[i] & 0xc0) != 0x80) {
			return -1;
		}
	}
	return len;
#endif
}