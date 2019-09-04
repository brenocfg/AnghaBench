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
typedef  int /*<<< orphan*/  u32 ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char*) ; 
 int /*<<< orphan*/  audit_panic (char*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  security_release_secctx (char*,unsigned int) ; 
 int security_secid_to_secctx (int /*<<< orphan*/ ,char**,unsigned int*) ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int audit_log_task_context(struct audit_buffer *ab)
{
	char *ctx = NULL;
	unsigned len;
	int error;
	u32 sid;

	security_task_getsecid(current, &sid);
	if (!sid)
		return 0;

	error = security_secid_to_secctx(sid, &ctx, &len);
	if (error) {
		if (error != -EINVAL)
			goto error_path;
		return 0;
	}

	audit_log_format(ab, " subj=%s", ctx);
	security_release_secctx(ctx, len);
	return 0;

error_path:
	audit_panic("error in audit_log_task_context");
	return error;
}