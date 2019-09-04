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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  Fbb (scalar_t__) ; 
 int /*<<< orphan*/  FbbTo (scalar_t__) ; 
 scalar_t__ UT64_MAX ; 
 scalar_t__ getCrossingBlock (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sdb_array_add_num (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_array_set_num (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_num_max (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_num_min (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_num_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bbAdd(Sdb *db, ut64 from, ut64 to, ut64 jump, ut64 fail) {
	ut64 block_start = getCrossingBlock (db, "bbs", from, to);
	int add = 1;
	if (block_start == UT64_MAX) {
		// add = 1;
	} else if (block_start == from) {
		// check if size is the same,
		add = 0;
	} else {
		/*
		   from = start address of new basic block
		   to = end address of new basic block
		   jump = destination basic block
		   fail = fallback jump of basic block
		   addr = previous closer basic block start address
		   addr_end = previous closer basic block start address
		 */
		// found a possible block
		if (from > block_start) {
			// from inside
			// RESIZE this
			sdb_num_set (db, Fbb(block_start), from, 0);
			sdb_num_set (db, FbbTo(block_start), from, 0);
			sdb_array_set_num (db, FbbTo(block_start), 0, from, 0);
			sdb_array_set_num (db, FbbTo(block_start), 1, UT64_MAX, 0);
		} else {
			// < the current runs into a known block
			to = block_start;
			jump = block_start;
			fail = UT64_MAX;
		}
	}
	if (add) {
		sdb_array_add_num (db, "bbs", from, 0);
		sdb_num_set (db, Fbb(from), to, 0);
		sdb_array_set_num (db, FbbTo(from), 0, jump, 0);
		sdb_array_set_num (db, FbbTo(from), 1, fail, 0);
		sdb_num_min (db, "min", from, 0);
		sdb_num_max (db, "max", to, 0);
	}
	return 0;
}