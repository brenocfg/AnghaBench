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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  uid ;
struct user_namespace {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  data; } ;
struct gss_upcall_msg {TYPE_1__ msg; int /*<<< orphan*/  databuf; int /*<<< orphan*/  uid; } ;
struct cred {struct user_namespace* user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gss_encode_v0_msg(struct gss_upcall_msg *gss_msg,
			      const struct cred *cred)
{
	struct user_namespace *userns = cred->user_ns;

	uid_t uid = from_kuid_munged(userns, gss_msg->uid);
	memcpy(gss_msg->databuf, &uid, sizeof(uid));
	gss_msg->msg.data = gss_msg->databuf;
	gss_msg->msg.len = sizeof(uid);

	BUILD_BUG_ON(sizeof(uid) > sizeof(gss_msg->databuf));
}