#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_core_key {int /*<<< orphan*/  k_dir_id; } ;
struct TYPE_3__ {int end; int search_start; struct in_core_key key; } ;
typedef  TYPE_1__ reiserfs_blocknr_hint_t ;
typedef  int b_blocknr_t ;

/* Variables and functions */
 int keyed_hash (char*,int) ; 

__attribute__((used)) static inline void hundredth_slices(reiserfs_blocknr_hint_t * hint)
{
	struct in_core_key *key = &hint->key;
	b_blocknr_t slice_start;

	slice_start =
	    (keyed_hash((char *)(&key->k_dir_id), 4) % 100) * (hint->end / 100);
	if (slice_start > hint->search_start
	    || slice_start + (hint->end / 100) <= hint->search_start) {
		hint->search_start = slice_start;
	}
}