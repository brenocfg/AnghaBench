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
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 

__attribute__((used)) static inline int pm3fb_shift_bpp(unsigned bpp, int v)
{
	switch (bpp) {
	case 8:
		return (v >> 4);
	case 16:
		return (v >> 3);
	case 32:
		return (v >> 2);
	}
	DPRINTK("Unsupported depth %u\n", bpp);
	return 0;
}