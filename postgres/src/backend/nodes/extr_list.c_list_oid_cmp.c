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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ListCell ;

/* Variables and functions */
 scalar_t__ lfirst_oid (int /*<<< orphan*/  const*) ; 

int
list_oid_cmp(const ListCell *p1, const ListCell *p2)
{
	Oid			v1 = lfirst_oid(p1);
	Oid			v2 = lfirst_oid(p2);

	if (v1 < v2)
		return -1;
	if (v1 > v2)
		return 1;
	return 0;
}