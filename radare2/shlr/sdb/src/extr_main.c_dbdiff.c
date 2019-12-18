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
 int /*<<< orphan*/  dbdiff_cb ; 
 int sdb_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdb_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dbdiff(const char *a, const char *b) {
	Sdb *A = sdb_new (NULL, a, 0);
	Sdb *B = sdb_new (NULL, b, 0);
	bool equal = sdb_diff (A, B, dbdiff_cb, NULL);
	sdb_free (A);
	sdb_free (B);
	return equal;
}