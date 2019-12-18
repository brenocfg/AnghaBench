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
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_count ; 
 int /*<<< orphan*/  lru_list ; 
 int /*<<< orphan*/  lru_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_glock_add_to_lru(struct gfs2_glock *gl)
{
	if (!(gl->gl_ops->go_flags & GLOF_LRU))
		return;

	spin_lock(&lru_lock);

	list_del(&gl->gl_lru);
	list_add_tail(&gl->gl_lru, &lru_list);

	if (!test_bit(GLF_LRU, &gl->gl_flags)) {
		set_bit(GLF_LRU, &gl->gl_flags);
		atomic_inc(&lru_count);
	}

	spin_unlock(&lru_lock);
}