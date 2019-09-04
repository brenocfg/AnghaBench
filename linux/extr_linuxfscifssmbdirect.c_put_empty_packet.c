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
struct smbd_response {int /*<<< orphan*/  list; } ;
struct smbd_connection {int /*<<< orphan*/  post_send_credits_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  empty_packet_queue_lock; int /*<<< orphan*/  count_empty_packet_queue; int /*<<< orphan*/  empty_packet_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_empty_packet(
		struct smbd_connection *info, struct smbd_response *response)
{
	spin_lock(&info->empty_packet_queue_lock);
	list_add_tail(&response->list, &info->empty_packet_queue);
	info->count_empty_packet_queue++;
	spin_unlock(&info->empty_packet_queue_lock);

	queue_work(info->workqueue, &info->post_send_credits_work);
}