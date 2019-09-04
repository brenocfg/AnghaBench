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
struct user_struct {scalar_t__ unix_inflight; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct user_struct* current_user () ; 
 scalar_t__ task_rlimit (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool too_many_unix_fds(struct task_struct *p)
{
	struct user_struct *user = current_user();

	if (unlikely(user->unix_inflight > task_rlimit(p, RLIMIT_NOFILE)))
		return !capable(CAP_SYS_RESOURCE) && !capable(CAP_SYS_ADMIN);
	return false;
}