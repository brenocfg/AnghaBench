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
struct sk_buff {int /*<<< orphan*/  destructor; void* sk; } ;
struct rfcomm_dev {int /*<<< orphan*/  wmem_alloc; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_wfree ; 
 int /*<<< orphan*/  tty_port_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_set_owner_w(struct sk_buff *skb, struct rfcomm_dev *dev)
{
	tty_port_get(&dev->port);
	atomic_inc(&dev->wmem_alloc);
	skb->sk = (void *) dev;
	skb->destructor = rfcomm_wfree;
}