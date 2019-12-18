#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ht; } ;
typedef  TYPE_1__ Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  sdb_ht_delete (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int _remove_afer_insert(void *user, const char *k, const char *v) {
	Sdb *s = (Sdb *)user;
	if (s) {
		sdb_ht_delete (s->ht, k);
		return true;
	}
	return false;
}