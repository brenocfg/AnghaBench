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

/* Variables and functions */
 int /*<<< orphan*/  r_hex_to_byte (int*,char const) ; 

__attribute__((used)) static inline ut8 rgbnum(const char ch1, const char ch2) {
	ut8 r = 0, r2 = 0;
	r_hex_to_byte (&r, ch1);
	r_hex_to_byte (&r2, ch2);
	return r << 4 | r2;
}