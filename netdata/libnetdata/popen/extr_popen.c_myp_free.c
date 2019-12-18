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
struct mypopen {struct mypopen* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (struct mypopen*) ; 
 int /*<<< orphan*/  myp_lock ; 
 scalar_t__ myp_tracking ; 
 struct mypopen* mypopen_root ; 
 int /*<<< orphan*/  netdata_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_mutex_unlock (int /*<<< orphan*/ *) ; 

void myp_free(void) {
    struct mypopen *mp, *next;

    if (myp_tracking == 0)
        return;

    netdata_mutex_lock(&myp_lock);
    for (mp = mypopen_root; mp != NULL; mp = next) {
        next = mp->next;
        freez(mp);
    }

    mypopen_root = NULL;
    myp_tracking = 0;
    netdata_mutex_unlock(&myp_lock);
}