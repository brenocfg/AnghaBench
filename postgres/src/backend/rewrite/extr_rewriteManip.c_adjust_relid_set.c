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
typedef  int /*<<< orphan*/  Relids ;

/* Variables and functions */
 int /*<<< orphan*/  bms_add_member (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bms_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_del_member (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bms_is_member (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Relids
adjust_relid_set(Relids relids, int oldrelid, int newrelid)
{
	if (bms_is_member(oldrelid, relids))
	{
		/* Ensure we have a modifiable copy */
		relids = bms_copy(relids);
		/* Remove old, add new */
		relids = bms_del_member(relids, oldrelid);
		relids = bms_add_member(relids, newrelid);
	}
	return relids;
}