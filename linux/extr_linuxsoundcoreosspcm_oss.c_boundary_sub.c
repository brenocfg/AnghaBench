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

__attribute__((used)) static int boundary_sub(int a, int adir,
			int b, int bdir,
			int *c, int *cdir)
{
	adir = adir < 0 ? -1 : (adir > 0 ? 1 : 0);
	bdir = bdir < 0 ? -1 : (bdir > 0 ? 1 : 0);
	*c = a - b;
	*cdir = adir - bdir;
	if (*cdir == -2) {
		(*c)--;
	} else if (*cdir == 2) {
		(*c)++;
	}
	return 0;
}