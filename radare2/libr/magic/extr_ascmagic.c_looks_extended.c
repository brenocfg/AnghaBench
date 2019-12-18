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
typedef  size_t ut8 ;
typedef  size_t unichar ;

/* Variables and functions */
 int I ; 
 int T ; 
 int X ; 
 int* text_chars ; 

__attribute__((used)) static int looks_extended(const ut8 *buf, size_t nbytes, unichar *ubuf, size_t *ulen) {
	size_t i;
	*ulen = 0;
	for (i = 0; i < nbytes; i++) {
		int t = text_chars[buf[i]];
		if (t != T && t != I && t != X) {
			return 0;
		}
		ubuf[(*ulen)++] = buf[i];
	}
	return 1;
}