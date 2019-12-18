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
struct TYPE_3__ {int numOfChildren; int /*<<< orphan*/ * Children; } ;
typedef  TYPE_1__ StringFileInfo ;
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  Pe_r_bin_store_string_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sdb_new0 () ; 
 int /*<<< orphan*/  sdb_ns_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static Sdb* Pe_r_bin_store_string_file_info(StringFileInfo* stringFileInfo) {
	char key[30];
	int i = 0;
	Sdb* sdb = NULL;
	if (!stringFileInfo) {
		return NULL;
	}
	sdb = sdb_new0 ();
	if (!sdb) {
		return NULL;
	}
	for (; i < stringFileInfo->numOfChildren; i++) {
		snprintf (key, 30, "stringtable%d", i);
		sdb_ns_set (sdb, key, Pe_r_bin_store_string_table (stringFileInfo->Children[i]));
	}
	return sdb;
}