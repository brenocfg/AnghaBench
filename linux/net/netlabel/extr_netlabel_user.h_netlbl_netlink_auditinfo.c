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
struct sk_buff {int dummy; } ;
struct netlbl_audit {int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; int /*<<< orphan*/  secid; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void netlbl_netlink_auditinfo(struct sk_buff *skb,
					    struct netlbl_audit *audit_info)
{
	security_task_getsecid(current, &audit_info->secid);
	audit_info->loginuid = audit_get_loginuid(current);
	audit_info->sessionid = audit_get_sessionid(current);
}