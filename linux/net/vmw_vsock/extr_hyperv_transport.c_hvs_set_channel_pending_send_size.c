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
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVS_PKT_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HVS_SEND_BUF_SIZE ; 
 int /*<<< orphan*/  set_channel_pending_send_size (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_mb () ; 

__attribute__((used)) static void hvs_set_channel_pending_send_size(struct vmbus_channel *chan)
{
	set_channel_pending_send_size(chan,
				      HVS_PKT_LEN(HVS_SEND_BUF_SIZE));

	virt_mb();
}