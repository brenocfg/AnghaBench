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
 int /*<<< orphan*/  sdb_disk_insert (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int _insert_into_disk(void *user, const char *key, const char *value) {
	Sdb *s = (Sdb *)user;
	if (s) {
		sdb_disk_insert (s, key, value);
		return true;
	}
	return false;
}