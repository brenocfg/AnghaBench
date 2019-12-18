#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ magic; } ;
struct TYPE_3__ {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ RELMAPPER_FILEMAGIC ; 
 int /*<<< orphan*/  load_relmap_file (int) ; 
 TYPE_2__ local_map ; 
 TYPE_1__ shared_map ; 

void
RelationMapInvalidateAll(void)
{
	if (shared_map.magic == RELMAPPER_FILEMAGIC)
		load_relmap_file(true);
	if (local_map.magic == RELMAPPER_FILEMAGIC)
		load_relmap_file(false);
}