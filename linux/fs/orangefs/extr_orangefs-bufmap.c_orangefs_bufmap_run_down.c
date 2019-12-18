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
struct orangefs_bufmap {int dummy; } ;

/* Variables and functions */
 struct orangefs_bufmap* __orangefs_bufmap ; 
 int /*<<< orphan*/  orangefs_bufmap_free (struct orangefs_bufmap*) ; 
 int /*<<< orphan*/  orangefs_bufmap_lock ; 
 int /*<<< orphan*/  orangefs_bufmap_unmap (struct orangefs_bufmap*) ; 
 int /*<<< orphan*/  readdir_map ; 
 int /*<<< orphan*/  run_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_map ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void orangefs_bufmap_run_down(void)
{
	struct orangefs_bufmap *bufmap = __orangefs_bufmap;
	if (!bufmap)
		return;
	run_down(&rw_map);
	run_down(&readdir_map);
	spin_lock(&orangefs_bufmap_lock);
	__orangefs_bufmap = NULL;
	spin_unlock(&orangefs_bufmap_lock);
	orangefs_bufmap_unmap(bufmap);
	orangefs_bufmap_free(bufmap);
}