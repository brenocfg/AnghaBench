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
typedef  int /*<<< orphan*/  HtPP ;

/* Variables and functions */
 int R_MIG_INDEX_LEN ; 
 char** mig_index ; 
 int /*<<< orphan*/  sdb_ht_insert (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * sdb_ht_new () ; 

__attribute__((used)) static HtPP *mig_hash_new() {
	HtPP *hash = sdb_ht_new ();
	if (!hash) {
		return NULL;
	}

	int i;
	for (i = 0; i < R_MIG_INDEX_LEN; i += 2) {
		const char *num = mig_index[i];
		const char *name = mig_index[i+1];
		sdb_ht_insert (hash, num, name);
	}

	return hash;
}