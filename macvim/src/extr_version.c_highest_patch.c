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
 int* included_patches ; 

int
highest_patch()
{
    int		i;
    int		h = 0;

    for (i = 0; included_patches[i] != 0; ++i)
	if (included_patches[i] > h)
	    h = included_patches[i];
    return h;
}