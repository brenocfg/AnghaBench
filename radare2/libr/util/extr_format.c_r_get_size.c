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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
typedef  int /*<<< orphan*/  RNum ;

/* Variables and functions */
 int r_num_math (int /*<<< orphan*/ *,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  updateAddr (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_get_size(RNum *num, ut8 *buf, int endian, const char *s) {
	int size = 0, len = strlen (s);
	ut64 addr;

	if (s[0] == '*' && len >= 4) { // value pointed by the address
		int offset = (int)r_num_math (num, s + 1);
		(void)updateAddr (buf + offset, 999, endian, &addr, NULL);
		return addr;
	} else {
		// flag handling doesnt seems to work here
		size = r_num_math (num, s);
	}
	return size;
}