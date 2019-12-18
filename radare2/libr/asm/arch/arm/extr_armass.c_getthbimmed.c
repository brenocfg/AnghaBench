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
typedef  int st32 ;

/* Variables and functions */

__attribute__((used)) static ut32 getthbimmed(st32 number) {
	ut32 res = 0;
	if (number < 0) {
		res |= 1 << 18;
	}
	number >>= 1;
	res |= (( number & 0xff) << 8);
	number >>= 8;
	res |= ( number & 0x07);
	number >>= 3;
	res |= (( number & 0xff) << 24);
	number >>= 8;
	res |= (( number & 0x3) << 16);
	number >>= 2;
	if (number < 0) {
		res |= (( number & 0x1) << 3);
		number >>= 1;
		res |= (( number & 0x1) << 5);
	} else {
		res |= ((!( number & 0x1)) << 3);
		number >>= 1;
		res |= ((!( number & 0x1)) << 5);
	}
	return res;
}