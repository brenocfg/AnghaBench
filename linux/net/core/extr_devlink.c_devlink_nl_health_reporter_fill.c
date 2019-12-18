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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink_health_reporter {int /*<<< orphan*/  dump_ts; scalar_t__ dump_fmsg; int /*<<< orphan*/  auto_recover; TYPE_1__* ops; int /*<<< orphan*/  graceful_period; int /*<<< orphan*/  recovery_count; int /*<<< orphan*/  error_count; int /*<<< orphan*/  health_state; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;
struct TYPE_2__ {scalar_t__ recover; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER_DUMP_TS ; 
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER_ERR_COUNT ; 
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD ; 
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER_RECOVER_COUNT ; 
 int /*<<< orphan*/  DEVLINK_ATTR_HEALTH_REPORTER_STATE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PAD ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 scalar_t__ devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devlink_nl_health_reporter_fill(struct sk_buff *msg,
				struct devlink *devlink,
				struct devlink_health_reporter *reporter,
				enum devlink_command cmd, u32 portid,
				u32 seq, int flags)
{
	struct nlattr *reporter_attr;
	void *hdr;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	if (devlink_nl_put_handle(msg, devlink))
		goto genlmsg_cancel;

	reporter_attr = nla_nest_start_noflag(msg,
					      DEVLINK_ATTR_HEALTH_REPORTER);
	if (!reporter_attr)
		goto genlmsg_cancel;
	if (nla_put_string(msg, DEVLINK_ATTR_HEALTH_REPORTER_NAME,
			   reporter->ops->name))
		goto reporter_nest_cancel;
	if (nla_put_u8(msg, DEVLINK_ATTR_HEALTH_REPORTER_STATE,
		       reporter->health_state))
		goto reporter_nest_cancel;
	if (nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_ERR_COUNT,
			      reporter->error_count, DEVLINK_ATTR_PAD))
		goto reporter_nest_cancel;
	if (nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_RECOVER_COUNT,
			      reporter->recovery_count, DEVLINK_ATTR_PAD))
		goto reporter_nest_cancel;
	if (reporter->ops->recover &&
	    nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD,
			      reporter->graceful_period,
			      DEVLINK_ATTR_PAD))
		goto reporter_nest_cancel;
	if (reporter->ops->recover &&
	    nla_put_u8(msg, DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER,
		       reporter->auto_recover))
		goto reporter_nest_cancel;
	if (reporter->dump_fmsg &&
	    nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_DUMP_TS,
			      jiffies_to_msecs(reporter->dump_ts),
			      DEVLINK_ATTR_PAD))
		goto reporter_nest_cancel;

	nla_nest_end(msg, reporter_attr);
	genlmsg_end(msg, hdr);
	return 0;

reporter_nest_cancel:
	nla_nest_end(msg, reporter_attr);
genlmsg_cancel:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}