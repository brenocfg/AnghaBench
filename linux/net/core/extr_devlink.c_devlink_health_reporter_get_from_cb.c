#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct netlink_callback {TYPE_1__* skb; int /*<<< orphan*/  extack; int /*<<< orphan*/  nlh; } ;
struct devlink_health_reporter {int dummy; } ;
struct devlink {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  policy; scalar_t__ hdrsize; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 scalar_t__ DEVLINK_ATTR_MAX ; 
 scalar_t__ GENL_HDRLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct devlink*) ; 
 struct devlink* devlink_get_from_attrs (int /*<<< orphan*/ ,struct nlattr**) ; 
 struct devlink_health_reporter* devlink_health_reporter_get_from_attrs (struct devlink*,struct nlattr**) ; 
 int /*<<< orphan*/  devlink_mutex ; 
 TYPE_2__ devlink_nl_family ; 
 int /*<<< orphan*/  kfree (struct nlattr**) ; 
 struct nlattr** kmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nlmsg_parse_deprecated (int /*<<< orphan*/ ,scalar_t__,struct nlattr**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct devlink_health_reporter *
devlink_health_reporter_get_from_cb(struct netlink_callback *cb)
{
	struct devlink_health_reporter *reporter;
	struct devlink *devlink;
	struct nlattr **attrs;
	int err;

	attrs = kmalloc_array(DEVLINK_ATTR_MAX + 1, sizeof(*attrs), GFP_KERNEL);
	if (!attrs)
		return NULL;

	err = nlmsg_parse_deprecated(cb->nlh,
				     GENL_HDRLEN + devlink_nl_family.hdrsize,
				     attrs, DEVLINK_ATTR_MAX,
				     devlink_nl_family.policy, cb->extack);
	if (err)
		goto free;

	mutex_lock(&devlink_mutex);
	devlink = devlink_get_from_attrs(sock_net(cb->skb->sk), attrs);
	if (IS_ERR(devlink))
		goto unlock;

	reporter = devlink_health_reporter_get_from_attrs(devlink, attrs);
	mutex_unlock(&devlink_mutex);
	kfree(attrs);
	return reporter;
unlock:
	mutex_unlock(&devlink_mutex);
free:
	kfree(attrs);
	return NULL;
}