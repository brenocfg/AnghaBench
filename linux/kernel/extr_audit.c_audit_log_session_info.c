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
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 unsigned int audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 

void audit_log_session_info(struct audit_buffer *ab)
{
	unsigned int sessionid = audit_get_sessionid(current);
	uid_t auid = from_kuid(&init_user_ns, audit_get_loginuid(current));

	audit_log_format(ab, "auid=%u ses=%u", auid, sessionid);
}