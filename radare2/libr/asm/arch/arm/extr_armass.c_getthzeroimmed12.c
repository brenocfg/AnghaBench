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

__attribute__((used)) static ut32 getthzeroimmed12(ut32 number) {
	ut32 res = 0;
	res |= (number & 0x800) << 7;
	res |= (number & 0x700) >> 4;
	res |= (number & 0x0ff) << 8;
	return res;
}