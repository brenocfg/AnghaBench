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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvec {void* iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int o2net_send_message_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvec*,int,int /*<<< orphan*/ ,int*) ; 

int o2net_send_message(u32 msg_type, u32 key, void *data, u32 len,
		       u8 target_node, int *status)
{
	struct kvec vec = {
		.iov_base = data,
		.iov_len = len,
	};
	return o2net_send_message_vec(msg_type, key, &vec, 1,
				      target_node, status);
}