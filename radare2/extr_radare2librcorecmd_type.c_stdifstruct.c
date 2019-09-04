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
 int /*<<< orphan*/  TDB_ ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 scalar_t__ r_str_startswith (char const*,char*) ; 
 char* sdb_const_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* sdb_fmt (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int stdifstruct(void *user, const char *k, const char *v) {
	r_return_val_if_fail (TDB_, false);
	if (!strcmp (v, "struct")) {
		return true;
	}
	if (!strcmp (v, "typedef")) {
		const char *typedef_key = sdb_fmt ("typedef.%s", k);
		const char *type = sdb_const_get (TDB_, typedef_key, NULL);
		if (type && r_str_startswith (type, "struct ")) {
			return true;
		}
	}
	return false;
}