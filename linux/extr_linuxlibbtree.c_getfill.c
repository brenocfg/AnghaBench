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
struct btree_geo {int no_pairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bval (struct btree_geo*,unsigned long*,int) ; 

__attribute__((used)) static int getfill(struct btree_geo *geo, unsigned long *node, int start)
{
	int i;

	for (i = start; i < geo->no_pairs; i++)
		if (!bval(geo, node, i))
			break;
	return i;
}