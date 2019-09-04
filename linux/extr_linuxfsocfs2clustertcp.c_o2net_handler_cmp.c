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
struct o2net_msg_handler {int /*<<< orphan*/  nh_msg_type; int /*<<< orphan*/  nh_key; } ;
typedef  int /*<<< orphan*/  msg_type ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int o2net_handler_cmp(struct o2net_msg_handler *nmh, u32 msg_type,
			     u32 key)
{
	int ret = memcmp(&nmh->nh_key, &key, sizeof(key));

	if (ret == 0)
		ret = memcmp(&nmh->nh_msg_type, &msg_type, sizeof(msg_type));

	return ret;
}