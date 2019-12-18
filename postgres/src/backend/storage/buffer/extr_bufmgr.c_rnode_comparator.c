#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ relNode; scalar_t__ dbNode; scalar_t__ spcNode; } ;
typedef  TYPE_1__ RelFileNode ;

/* Variables and functions */

__attribute__((used)) static int
rnode_comparator(const void *p1, const void *p2)
{
	RelFileNode n1 = *(const RelFileNode *) p1;
	RelFileNode n2 = *(const RelFileNode *) p2;

	if (n1.relNode < n2.relNode)
		return -1;
	else if (n1.relNode > n2.relNode)
		return 1;

	if (n1.dbNode < n2.dbNode)
		return -1;
	else if (n1.dbNode > n2.dbNode)
		return 1;

	if (n1.spcNode < n2.spcNode)
		return -1;
	else if (n1.spcNode > n2.spcNode)
		return 1;
	else
		return 0;
}