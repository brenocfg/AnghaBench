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
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;

/* Variables and functions */
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 

unsigned long ubifs_shrink_count(struct shrinker *shrink,
				 struct shrink_control *sc)
{
	long clean_zn_cnt = atomic_long_read(&ubifs_clean_zn_cnt);

	/*
	 * Due to the way UBIFS updates the clean znode counter it may
	 * temporarily be negative.
	 */
	return clean_zn_cnt >= 0 ? clean_zn_cnt : 1;
}