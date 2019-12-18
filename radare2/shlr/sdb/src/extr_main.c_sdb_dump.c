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
 int sdb_grep_dump (char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdb_dump(const char *db, int fmt) {
	return sdb_grep_dump (db, fmt, false, NULL);
}