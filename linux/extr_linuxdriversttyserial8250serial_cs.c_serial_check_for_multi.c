#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serial_info {int multi; } ;
struct pcmcia_device {TYPE_1__** resource; struct serial_info* priv; } ;
struct TYPE_2__ {int end; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int serial_check_for_multi(struct pcmcia_device *p_dev,  void *priv_data)
{
	struct serial_info *info = p_dev->priv;

	if (!p_dev->resource[0]->end)
		return -EINVAL;

	if ((!p_dev->resource[1]->end) && (p_dev->resource[0]->end % 8 == 0))
		info->multi = p_dev->resource[0]->end >> 3;

	if ((p_dev->resource[1]->end) && (p_dev->resource[0]->end == 8)
		&& (p_dev->resource[1]->end == 8))
		info->multi = 2;

	return 0; /* break */
}