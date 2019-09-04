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
struct ore_layout {int dummy; } ;
struct ore_io_state {int dummy; } ;
struct ore_components {int /*<<< orphan*/  numdevs; } ;

/* Variables and functions */
 int _ore_get_io_state (struct ore_layout*,struct ore_components*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ore_io_state**) ; 

int  ore_get_io_state(struct ore_layout *layout, struct ore_components *oc,
		      struct ore_io_state **pios)
{
	return _ore_get_io_state(layout, oc, oc->numdevs, 0, 0, pios);
}