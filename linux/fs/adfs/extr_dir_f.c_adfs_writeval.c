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

/* Variables and functions */

__attribute__((used)) static inline void adfs_writeval(unsigned char *p, int len, unsigned int val)
{
	switch (len) {
	case 4:		p[3] = val >> 24;
			/* fall through */
	case 3:		p[2] = val >> 16;
			/* fall through */
	case 2:		p[1] = val >> 8;
			/* fall through */
	default:	p[0] = val;
	}
}