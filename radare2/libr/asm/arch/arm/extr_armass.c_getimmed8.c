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
typedef  int ut32 ;

/* Variables and functions */
 int err ; 
 int getnum (char const*) ; 

__attribute__((used)) static ut32 getimmed8(const char *str) {
	ut32 num = getnum (str);
	if (err) {
		return 0;
	}
	ut32 rotate;
	if (num <= 0xff) {
		return num;
	} else {
		for (rotate = 1; rotate < 16; rotate++) {
			// rol 2
			num = ((num << 2) | (num >> 30));
			if (num == (num & 0xff)) {
				return (num | (rotate << 8));
			}
		}
		err = 1;
		return 0;
	}
}