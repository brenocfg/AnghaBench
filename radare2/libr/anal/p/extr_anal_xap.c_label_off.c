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
struct directive {int d_operand; int d_prefix; int d_off; } ;

/* Variables and functions */

__attribute__((used)) static int label_off(struct directive *d) {
	int off = d->d_operand;
	int lame = off & 0x80;

	if (!d->d_prefix) { // WTF
		off = (char) (off & 0xff);
	} else if (d->d_prefix == 1) {
		off = (short) (off & 0xffff);
		if (lame) {
			off -= 0x100;
		}
	} else {
		off = (int) (off & 0xffffff);
		if (off & 0x800000) {
			off |= 0xff000000;
		}
		if (off & 0x8000) {
			off -= 0x10000;
		}
		if (lame) {
			off -= 0x100;
		}
	}
	return d->d_off + off;
}