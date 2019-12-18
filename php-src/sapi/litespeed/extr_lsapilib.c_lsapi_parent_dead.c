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
 scalar_t__ EPERM ; 
 scalar_t__ errno ; 
 scalar_t__ getppid () ; 
 int kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ s_ppid ; 
 scalar_t__ s_restored_ppid ; 

__attribute__((used)) static int lsapi_parent_dead()
{
    // Return non-zero if the parent is dead.  0 if still alive.
    if (!s_ppid) {
        // not checking, so not dead
        return(0);
    }
    if (s_restored_ppid) {
        if (kill(s_restored_ppid,0) == -1) {
            if (errno == EPERM) {
                return(0); // no permission, but it's still there.
            }
            return(1); // Dead
        }
        return(0); // it worked, so it's not dead
    }
    return(s_ppid != getppid());
}