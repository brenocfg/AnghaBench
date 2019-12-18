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
struct kimage {scalar_t__* entry; } ;

/* Variables and functions */
 scalar_t__ IND_DONE ; 

void kimage_terminate(struct kimage *image)
{
	if (*image->entry != 0)
		image->entry++;

	*image->entry = IND_DONE;
}