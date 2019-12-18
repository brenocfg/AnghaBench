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
struct file_lock {int /*<<< orphan*/  fl_wait; int /*<<< orphan*/  fl_blocked_member; int /*<<< orphan*/  fl_blocked_requests; int /*<<< orphan*/  fl_list; int /*<<< orphan*/  fl_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locks_init_lock_heads(struct file_lock *fl)
{
	INIT_HLIST_NODE(&fl->fl_link);
	INIT_LIST_HEAD(&fl->fl_list);
	INIT_LIST_HEAD(&fl->fl_blocked_requests);
	INIT_LIST_HEAD(&fl->fl_blocked_member);
	init_waitqueue_head(&fl->fl_wait);
}