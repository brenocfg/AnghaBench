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
struct orangefs_bufmap {int desc_size; } ;

/* Variables and functions */
 struct orangefs_bufmap* __orangefs_bufmap ; 
 int /*<<< orphan*/  orangefs_bufmap_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int orangefs_bufmap_size_query(void)
{
	struct orangefs_bufmap *bufmap;
	int size = 0;
	spin_lock(&orangefs_bufmap_lock);
	bufmap = __orangefs_bufmap;
	if (bufmap)
		size = bufmap->desc_size;
	spin_unlock(&orangefs_bufmap_lock);
	return size;
}