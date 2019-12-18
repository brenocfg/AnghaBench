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
struct virtual_item {struct direntry_uarea* vi_uarea; } ;
struct direntry_uarea {int entry_count; } ;

/* Variables and functions */

__attribute__((used)) static int direntry_unit_num(struct virtual_item *vi)
{
	struct direntry_uarea *dir_u = vi->vi_uarea;

	return dir_u->entry_count;
}