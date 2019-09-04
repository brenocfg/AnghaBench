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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ check_for_new_mountpoints_every ; 
 int /*<<< orphan*/  disk_mountinfo_root ; 
 int /*<<< orphan*/  mountinfo_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mountinfo_read (int /*<<< orphan*/ ) ; 
 scalar_t__ now_realtime_sec () ; 

__attribute__((used)) static inline void mountinfo_reload(int force) {
    static time_t last_loaded = 0;
    time_t now = now_realtime_sec();

    if(force || now - last_loaded >= check_for_new_mountpoints_every) {
        // mountinfo_free_all() can be called with NULL disk_mountinfo_root
        mountinfo_free_all(disk_mountinfo_root);

        // re-read mountinfo in case something changed
        disk_mountinfo_root = mountinfo_read(0);

        last_loaded = now;
    }
}