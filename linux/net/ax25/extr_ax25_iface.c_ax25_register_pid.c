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
struct ax25_protocol {struct ax25_protocol* next; } ;

/* Variables and functions */
 struct ax25_protocol* protocol_list ; 
 int /*<<< orphan*/  protocol_list_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ax25_register_pid(struct ax25_protocol *ap)
{
	write_lock_bh(&protocol_list_lock);
	ap->next = protocol_list;
	protocol_list = ap;
	write_unlock_bh(&protocol_list_lock);
}