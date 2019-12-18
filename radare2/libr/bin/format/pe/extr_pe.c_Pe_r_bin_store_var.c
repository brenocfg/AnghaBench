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
struct TYPE_3__ {unsigned int numOfValues; int /*<<< orphan*/ * Value; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/ * sdb_new0 () ; 
 int /*<<< orphan*/  sdb_num_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static Sdb* Pe_r_bin_store_var(Var* var) {
	unsigned int i = 0;
	char key[20];
	Sdb* sdb = NULL;
	if (var) {
		sdb = sdb_new0 ();
		if (sdb) {
			for (; i < var->numOfValues; i++) {
				snprintf (key, 20, "%d", i);
				sdb_num_set (sdb, key, var->Value[i], 0);
			}
		}
	}
	return sdb;
}