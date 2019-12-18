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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  vcc_sklist_lock ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vcc_remove_socket(struct sock *sk)
{
	write_lock_irq(&vcc_sklist_lock);
	sk_del_node_init(sk);
	write_unlock_irq(&vcc_sklist_lock);
}