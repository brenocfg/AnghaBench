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
typedef  scalar_t__ zorro_id ;
struct zorro_dev {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ ZORRO_WILDCARD ; 
 struct zorro_dev* zorro_autocon ; 
 int zorro_num_autocon ; 

struct zorro_dev *zorro_find_device(zorro_id id, struct zorro_dev *from)
{
	struct zorro_dev *z;

	if (!zorro_num_autocon)
		return NULL;

	for (z = from ? from+1 : &zorro_autocon[0];
	     z < zorro_autocon+zorro_num_autocon;
	     z++)
		if (id == ZORRO_WILDCARD || id == z->id)
			return z;
	return NULL;
}