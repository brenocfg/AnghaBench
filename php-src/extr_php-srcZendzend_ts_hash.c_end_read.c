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
typedef  int /*<<< orphan*/  TsHashTable ;

/* Variables and functions */

__attribute__((used)) static void end_read(TsHashTable *ht)
{
#ifdef ZTS
	tsrm_mutex_lock(ht->mx_reader);
	if ((--(ht->reader)) == 0) {
		tsrm_mutex_unlock(ht->mx_writer);
	}
	tsrm_mutex_unlock(ht->mx_reader);
#endif
}