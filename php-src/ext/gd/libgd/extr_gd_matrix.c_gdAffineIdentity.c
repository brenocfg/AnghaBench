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
 int GD_TRUE ; 

int gdAffineIdentity (double dst[6])
{
	dst[0] = 1;
	dst[1] = 0;
	dst[2] = 0;
	dst[3] = 1;
	dst[4] = 0;
	dst[5] = 0;
	return GD_TRUE;
}