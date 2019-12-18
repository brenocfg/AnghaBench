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
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ u16 ;
struct audit_context {int dummy; } ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ AUDIT_USER_AVC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_session_info (struct audit_buffer*) ; 
 struct audit_buffer* audit_log_start (struct audit_context*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  audit_log_task_context (struct audit_buffer*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  task_tgid_nr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void audit_log_common_recv_msg(struct audit_context *context,
					struct audit_buffer **ab, u16 msg_type)
{
	uid_t uid = from_kuid(&init_user_ns, current_uid());
	pid_t pid = task_tgid_nr(current);

	if (!audit_enabled && msg_type != AUDIT_USER_AVC) {
		*ab = NULL;
		return;
	}

	*ab = audit_log_start(context, GFP_KERNEL, msg_type);
	if (unlikely(!*ab))
		return;
	audit_log_format(*ab, "pid=%d uid=%u ", pid, uid);
	audit_log_session_info(*ab);
	audit_log_task_context(*ab);
}