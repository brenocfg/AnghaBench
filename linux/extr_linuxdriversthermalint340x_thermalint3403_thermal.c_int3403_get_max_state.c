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
struct thermal_cooling_device {struct int3403_priv* devdata; } ;
struct int3403_priv {struct int3403_cdev* priv; } ;
struct int3403_cdev {unsigned long max_state; } ;

/* Variables and functions */

__attribute__((used)) static int int3403_get_max_state(struct thermal_cooling_device *cdev,
				 unsigned long *state)
{
	struct int3403_priv *priv = cdev->devdata;
	struct int3403_cdev *obj = priv->priv;

	*state = obj->max_state;
	return 0;
}