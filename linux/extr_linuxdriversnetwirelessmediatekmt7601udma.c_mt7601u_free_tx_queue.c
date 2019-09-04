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
struct mt7601u_tx_queue {int entries; TYPE_1__* e; int /*<<< orphan*/  used; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7601u_free_tx_queue(struct mt7601u_tx_queue *q)
{
	int i;

	WARN_ON(q->used);

	for (i = 0; i < q->entries; i++)  {
		usb_poison_urb(q->e[i].urb);
		usb_free_urb(q->e[i].urb);
	}
}