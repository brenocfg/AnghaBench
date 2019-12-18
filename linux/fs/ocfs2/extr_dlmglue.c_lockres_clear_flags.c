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
struct ocfs2_lock_res {unsigned long l_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockres_set_flags (struct ocfs2_lock_res*,unsigned long) ; 

__attribute__((used)) static void lockres_clear_flags(struct ocfs2_lock_res *lockres,
				unsigned long clear)
{
	lockres_set_flags(lockres, lockres->l_flags & ~clear);
}