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
struct sst_dev_stream_map {int dev_num; int direction; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sst_get_stream_mapping(int dev, int sdev, int dir,
	struct sst_dev_stream_map *map, int size)
{
	int i;

	if (map == NULL)
		return -EINVAL;


	/* index 0 is not used in stream map */
	for (i = 1; i < size; i++) {
		if ((map[i].dev_num == dev) && (map[i].direction == dir))
			return i;
	}
	return 0;
}