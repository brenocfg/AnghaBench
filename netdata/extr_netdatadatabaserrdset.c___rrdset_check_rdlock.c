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
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  rrdset_rwlock; } ;
typedef  TYPE_1__ RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRD_CALLS ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,char const*,unsigned long const,char const*) ; 
 int netdata_rwlock_trywrlock (int /*<<< orphan*/ *) ; 

void __rrdset_check_rdlock(RRDSET *st, const char *file, const char *function, const unsigned long line) {
    debug(D_RRD_CALLS, "Checking read lock on chart '%s'", st->id);

    int ret = netdata_rwlock_trywrlock(&st->rrdset_rwlock);
    if(ret == 0)
        fatal("RRDSET '%s' should be read-locked, but it is not, at function %s() at line %lu of file '%s'", st->id, function, line, file);
}