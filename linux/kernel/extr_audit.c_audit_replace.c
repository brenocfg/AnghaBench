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
struct pid {int dummy; } ;
typedef  int /*<<< orphan*/  pvnr ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_REPLACE ; 
 int ENOMEM ; 
 struct sk_buff* audit_make_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int auditd_send_unicast_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pid_vnr (struct pid*) ; 

__attribute__((used)) static int audit_replace(struct pid *pid)
{
	pid_t pvnr;
	struct sk_buff *skb;

	pvnr = pid_vnr(pid);
	skb = audit_make_reply(0, AUDIT_REPLACE, 0, 0, &pvnr, sizeof(pvnr));
	if (!skb)
		return -ENOMEM;
	return auditd_send_unicast_skb(skb);
}