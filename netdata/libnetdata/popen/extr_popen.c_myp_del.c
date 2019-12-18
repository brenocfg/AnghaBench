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
struct mypopen {scalar_t__ pid; struct mypopen* next; TYPE_1__* prev; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {struct mypopen* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  freez (struct mypopen*) ; 
 int /*<<< orphan*/  myp_lock ; 
 scalar_t__ myp_tracking ; 
 struct mypopen* mypopen_root ; 
 int /*<<< orphan*/  netdata_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void myp_del(pid_t pid) {
    struct mypopen *mp;

    if (myp_tracking == 0)
        return;

    netdata_mutex_lock(&myp_lock);
    for (mp = mypopen_root; mp != NULL; mp = mp->next) {
        if (mp->pid == pid) {
            if (mp->next != NULL)
                mp->next->prev = mp->prev;
            if (mp->prev != NULL)
                mp->prev->next = mp->next;
            if (mypopen_root == mp)
                mypopen_root = mp->next;
            freez(mp);
            break;
        }
    }

    if (mp == NULL)
        error("Cannot find pid %d.", pid);

    netdata_mutex_unlock(&myp_lock);
}