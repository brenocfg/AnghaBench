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
struct zorro_device_id {scalar_t__ id; } ;
struct zorro_dev {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ ZORRO_WILDCARD ; 

const struct zorro_device_id *
zorro_match_device(const struct zorro_device_id *ids,
		   const struct zorro_dev *z)
{
	while (ids->id) {
		if (ids->id == ZORRO_WILDCARD || ids->id == z->id)
			return ids;
		ids++;
	}
	return NULL;
}