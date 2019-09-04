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
struct map {TYPE_1__* dso; } ;
struct kmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kernel; } ;

/* Variables and functions */

struct kmap *__map__kmap(struct map *map)
{
	if (!map->dso || !map->dso->kernel)
		return NULL;
	return (struct kmap *)(map + 1);
}