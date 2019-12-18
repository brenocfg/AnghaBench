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
typedef  int int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_G_INPUT ; 
 int /*<<< orphan*/  VIDIOC_S_INPUT ; 
 int v4l2_ioctl (int,int /*<<< orphan*/ ,int*) ; 

int_fast32_t v4l2_set_input(int_fast32_t dev, int *input)
{
	if (!dev || !input)
		return -1;

	return (*input == -1) ? v4l2_ioctl(dev, VIDIOC_G_INPUT, input)
			      : v4l2_ioctl(dev, VIDIOC_S_INPUT, input);
}