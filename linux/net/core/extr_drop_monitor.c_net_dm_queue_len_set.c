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
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 size_t NET_DM_ATTR_QUEUE_LEN ; 
 int /*<<< orphan*/  net_dm_queue_len ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void net_dm_queue_len_set(struct genl_info *info)
{
	if (!info->attrs[NET_DM_ATTR_QUEUE_LEN])
		return;

	net_dm_queue_len = nla_get_u32(info->attrs[NET_DM_ATTR_QUEUE_LEN]);
}