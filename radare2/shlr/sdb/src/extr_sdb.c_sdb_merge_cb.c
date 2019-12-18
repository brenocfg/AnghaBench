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
 int /*<<< orphan*/  sdb_set (void*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdb_merge_cb(void *user, const char *k, const char *v) {
	sdb_set (user, k, v, 0);
	return true;
}