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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debug_kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** kdb_name_table ; 

void kdbnearsym_cleanup(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(kdb_name_table); ++i) {
		if (kdb_name_table[i]) {
			debug_kfree(kdb_name_table[i]);
			kdb_name_table[i] = NULL;
		}
	}
}