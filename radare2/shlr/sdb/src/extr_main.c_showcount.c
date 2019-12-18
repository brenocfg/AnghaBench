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
typedef  int ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdb_stats (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

int showcount(const char *db) {
	ut32 d;
	s = sdb_new (NULL, db, 0);
	if (sdb_stats (s, &d, NULL)) {
		printf ("%d\n", d);
	}
	// TODO: show version, timestamp information
	sdb_free (s);
	return 0;
}