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
struct slabinfo {scalar_t__ alias; } ;

/* Variables and functions */
 int /*<<< orphan*/  ops (struct slabinfo*) ; 
 int output_lines ; 
 int /*<<< orphan*/  report (struct slabinfo*) ; 
 scalar_t__ set_debug ; 
 scalar_t__ show_numa ; 
 scalar_t__ show_ops ; 
 scalar_t__ show_report ; 
 scalar_t__ show_slab ; 
 scalar_t__ show_track ; 
 int /*<<< orphan*/  show_tracking (struct slabinfo*) ; 
 scalar_t__ shrink ; 
 int /*<<< orphan*/  slab_debug (struct slabinfo*) ; 
 int /*<<< orphan*/  slab_numa (struct slabinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slab_shrink (struct slabinfo*) ; 
 int /*<<< orphan*/  slab_validate (struct slabinfo*) ; 
 int /*<<< orphan*/  slabcache (struct slabinfo*) ; 
 struct slabinfo* slabinfo ; 
 int slabs ; 
 scalar_t__ validate ; 

__attribute__((used)) static void output_slabs(void)
{
	struct slabinfo *slab;
	int lines = output_lines;

	for (slab = slabinfo; (slab < slabinfo + slabs) &&
			lines != 0; slab++) {

		if (slab->alias)
			continue;

		if (lines != -1)
			lines--;

		if (show_numa)
			slab_numa(slab, 0);
		else if (show_track)
			show_tracking(slab);
		else if (validate)
			slab_validate(slab);
		else if (shrink)
			slab_shrink(slab);
		else if (set_debug)
			slab_debug(slab);
		else if (show_ops)
			ops(slab);
		else if (show_slab)
			slabcache(slab);
		else if (show_report)
			report(slab);
	}
}