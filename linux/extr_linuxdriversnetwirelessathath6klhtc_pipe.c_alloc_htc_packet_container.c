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
struct TYPE_4__ {struct htc_packet* htc_packet_pool; } ;
struct htc_target {int /*<<< orphan*/  rx_lock; TYPE_2__ pipe; } ;
struct TYPE_3__ {int /*<<< orphan*/ * next; } ;
struct htc_packet {TYPE_1__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct htc_packet *alloc_htc_packet_container(struct htc_target *target)
{
	struct htc_packet *packet;
	spin_lock_bh(&target->rx_lock);

	if (target->pipe.htc_packet_pool == NULL) {
		spin_unlock_bh(&target->rx_lock);
		return NULL;
	}

	packet = target->pipe.htc_packet_pool;
	target->pipe.htc_packet_pool = (struct htc_packet *) packet->list.next;

	spin_unlock_bh(&target->rx_lock);

	packet->list.next = NULL;
	return packet;
}