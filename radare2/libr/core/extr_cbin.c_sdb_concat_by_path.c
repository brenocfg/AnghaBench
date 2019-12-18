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
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  sdb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdb_new (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdb_concat_by_path(Sdb *s, const char *path) {
	Sdb *db = sdb_new (0, path, 0);
	sdb_merge (s, db);
	sdb_close (db);
	sdb_free (db);
}