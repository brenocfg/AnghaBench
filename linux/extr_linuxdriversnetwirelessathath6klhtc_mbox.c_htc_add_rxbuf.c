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
struct list_head {int dummy; } ;
struct htc_target {int dummy; } ;
struct htc_packet {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int ath6kl_htc_mbox_add_rxbuf_multiple (struct htc_target*,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int htc_add_rxbuf(struct htc_target *target, struct htc_packet *packet)
{
	struct list_head queue;

	INIT_LIST_HEAD(&queue);
	list_add_tail(&packet->list, &queue);
	return ath6kl_htc_mbox_add_rxbuf_multiple(target, &queue);
}