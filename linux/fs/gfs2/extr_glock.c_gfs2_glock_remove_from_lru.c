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
struct gfs2_glock {int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_lru; TYPE_1__* gl_ops; } ;
struct TYPE_2__ {int go_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLF_LRU ; 
 int GLOF_LRU ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_count ; 
 int /*<<< orphan*/  lru_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfs2_glock_remove_from_lru(struct gfs2_glock *gl)
{
	if (!(gl->gl_ops->go_flags & GLOF_LRU))
		return;

	spin_lock(&lru_lock);
	if (test_bit(GLF_LRU, &gl->gl_flags)) {
		list_del_init(&gl->gl_lru);
		atomic_dec(&lru_count);
		clear_bit(GLF_LRU, &gl->gl_flags);
	}
	spin_unlock(&lru_lock);
}