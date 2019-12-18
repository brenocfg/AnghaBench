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
struct gcov_info {int /*<<< orphan*/  head; int /*<<< orphan*/  functions; } ;
typedef  int /*<<< orphan*/  (* llvm_gcov_callback ) () ;

/* Variables and functions */
 int /*<<< orphan*/  GCOV_ADD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clang_gcov_list ; 
 struct gcov_info* current_info ; 
 int /*<<< orphan*/  gcov_event (int /*<<< orphan*/ ,struct gcov_info*) ; 
 scalar_t__ gcov_events_enabled ; 
 int /*<<< orphan*/  gcov_lock ; 
 struct gcov_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void llvm_gcov_init(llvm_gcov_callback writeout, llvm_gcov_callback flush)
{
	struct gcov_info *info = kzalloc(sizeof(*info), GFP_KERNEL);

	if (!info)
		return;

	INIT_LIST_HEAD(&info->head);
	INIT_LIST_HEAD(&info->functions);

	mutex_lock(&gcov_lock);

	list_add_tail(&info->head, &clang_gcov_list);
	current_info = info;
	writeout();
	current_info = NULL;
	if (gcov_events_enabled)
		gcov_event(GCOV_ADD, info);

	mutex_unlock(&gcov_lock);
}