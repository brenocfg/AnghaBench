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
struct pcm_info {int dummy; } ;
struct i2sbus_dev {struct pcm_info in; struct pcm_info out; } ;

/* Variables and functions */

__attribute__((used)) static inline void get_pcm_info(struct i2sbus_dev *i2sdev, int in,
				struct pcm_info **pi, struct pcm_info **other)
{
	if (in) {
		if (pi)
			*pi = &i2sdev->in;
		if (other)
			*other = &i2sdev->out;
	} else {
		if (pi)
			*pi = &i2sdev->out;
		if (other)
			*other = &i2sdev->in;
	}
}