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
struct mypopen {struct mypopen* prev; struct mypopen* next; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct mypopen* mallocz (int) ; 
 int /*<<< orphan*/  myp_lock ; 
 scalar_t__ myp_tracking ; 
 struct mypopen* mypopen_root ; 
 int /*<<< orphan*/  netdata_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void myp_add_locked(pid_t pid) {
    struct mypopen *mp;

    if (myp_tracking == 0)
        return;

    mp = mallocz(sizeof(struct mypopen));
    mp->pid = pid;

    mp->next = mypopen_root;
    mp->prev = NULL;
    if (mypopen_root != NULL)
        mypopen_root->prev = mp;
    mypopen_root = mp;
    netdata_mutex_unlock(&myp_lock);
}