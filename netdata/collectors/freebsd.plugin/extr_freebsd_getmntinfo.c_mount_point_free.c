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
struct mount_point {struct mount_point* name; int /*<<< orphan*/  st_inodes; int /*<<< orphan*/  st_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (struct mount_point*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_points_added ; 
 int /*<<< orphan*/  rrdset_is_obsolete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_point_free(struct mount_point *m) {
    if (likely(m->st_space))
        rrdset_is_obsolete(m->st_space);
    if (likely(m->st_inodes))
        rrdset_is_obsolete(m->st_inodes);

    mount_points_added--;
    freez(m->name);
    freez(m);
}