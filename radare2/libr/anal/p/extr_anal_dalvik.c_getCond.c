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

__attribute__((used)) static const char *getCond(ut8 cond) {
	switch (cond) {
	case 0x32: // if-eq
		return "$z";
	case 0x33: // if-ne
		return "$z,!";
	case 0x34: // if-lt
		return "63,$c,!";
	case 0x35: // if-ge
		return "63,$c,$z,|";
	case 0x36: // if-gt
		return "63,$c";
	case 0x37: // if-le
		return "63,$c,!,$z,|";
	}
	return "";
}