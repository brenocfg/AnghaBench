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

__attribute__((used)) static const char *getCondz(ut8 cond) {
	switch (cond) {
	case 0x38: // if-eqz
		return "NOP";
	case 0x39: // if-nez
		return "!";
	case 0x3a: // if-ltz
		return "0,==,63,$c,!";
	case 0x3b: // if-gez
		return "0,==,63,$c,$z,|";
	case 0x3c: // if-gtz
		return "0,==,63,$c";
	case 0x3d: // if-lez
		return "0,==,63,$c,!";
	}
	return "";
}