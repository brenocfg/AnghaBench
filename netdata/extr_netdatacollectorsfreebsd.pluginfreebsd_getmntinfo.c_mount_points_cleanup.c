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
struct mount_point {struct mount_point* next; scalar_t__ updated; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mount_point_free (struct mount_point*) ; 
 scalar_t__ mount_points_added ; 
 scalar_t__ mount_points_found ; 
 struct mount_point* mount_points_last_used ; 
 struct mount_point* mount_points_root ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mount_points_cleanup() {
    if (likely(mount_points_found == mount_points_added)) return;

    struct mount_point *m = mount_points_root, *last = NULL;
    while(m) {
        if (unlikely(!m->updated)) {
            // info("Removing mount point '%s', linked after '%s'", m->name, last?last->name:"ROOT");

            if (mount_points_last_used == m)
                mount_points_last_used = last;

            struct mount_point *t = m;

            if (m == mount_points_root || !last)
                mount_points_root = m = m->next;

            else
                last->next = m = m->next;

            t->next = NULL;
            mount_point_free(t);
        }
        else {
            last = m;
            m->updated = 0;
            m = m->next;
        }
    }
}