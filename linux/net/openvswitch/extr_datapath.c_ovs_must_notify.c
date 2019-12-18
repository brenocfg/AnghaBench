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
struct genl_info {TYPE_1__* nlhdr; } ;
struct genl_family {int dummy; } ;
struct TYPE_2__ {int nlmsg_flags; } ;

/* Variables and functions */
 int NLM_F_ECHO ; 
 scalar_t__ genl_has_listeners (struct genl_family*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 

__attribute__((used)) static bool ovs_must_notify(struct genl_family *family, struct genl_info *info,
			    unsigned int group)
{
	return info->nlhdr->nlmsg_flags & NLM_F_ECHO ||
	       genl_has_listeners(family, genl_info_net(info), group);
}