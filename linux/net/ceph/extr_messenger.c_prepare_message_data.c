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
typedef  scalar_t__ u32 ;
struct ceph_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_msg_data_cursor_init (struct ceph_msg*,size_t) ; 

__attribute__((used)) static void prepare_message_data(struct ceph_msg *msg, u32 data_len)
{
	/* Initialize data cursor */

	ceph_msg_data_cursor_init(msg, (size_t)data_len);
}