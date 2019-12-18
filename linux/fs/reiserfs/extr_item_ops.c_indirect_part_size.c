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
struct virtual_item {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int indirect_part_size(struct virtual_item *vi, int first, int units)
{
	/* unit of indirect item is byte (yet) */
	return units;
}