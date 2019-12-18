#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {scalar_t__ bus_type; int /*<<< orphan*/  compatible; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 struct device* bus_find_device_by_of_node (scalar_t__,struct device_node*) ; 
 TYPE_1__* dailink_match ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static int rockchip_sound_codec_node_match(struct device_node *np_codec)
{
	struct device *dev;
	int i;

	for (i = 0; i < ARRAY_SIZE(dailink_match); i++) {
		if (!of_device_is_compatible(np_codec,
					     dailink_match[i].compatible))
			continue;

		if (dailink_match[i].bus_type) {
			dev = bus_find_device_by_of_node(dailink_match[i].bus_type,
							 np_codec);
			if (!dev)
				continue;
			put_device(dev);
		}

		return i;
	}
	return -1;
}