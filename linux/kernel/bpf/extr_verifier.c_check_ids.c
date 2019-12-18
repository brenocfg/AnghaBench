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
typedef  scalar_t__ u32 ;
struct idpair {scalar_t__ old; scalar_t__ cur; } ;

/* Variables and functions */
 unsigned int ID_MAP_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static bool check_ids(u32 old_id, u32 cur_id, struct idpair *idmap)
{
	unsigned int i;

	for (i = 0; i < ID_MAP_SIZE; i++) {
		if (!idmap[i].old) {
			/* Reached an empty slot; haven't seen this id before */
			idmap[i].old = old_id;
			idmap[i].cur = cur_id;
			return true;
		}
		if (idmap[i].old == old_id)
			return idmap[i].cur == cur_id;
	}
	/* We ran out of idmap slots, which should be impossible */
	WARN_ON_ONCE(1);
	return false;
}