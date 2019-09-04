#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t call_id; } ;
struct TYPE_5__ {TYPE_1__ src_addr; } ;
struct TYPE_6__ {TYPE_2__ pptp; } ;
struct pppox_sock {TYPE_3__ proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callid_bitmap ; 
 int /*<<< orphan*/ * callid_sock ; 
 int /*<<< orphan*/  chan_lock ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void del_chan(struct pppox_sock *sock)
{
	spin_lock(&chan_lock);
	clear_bit(sock->proto.pptp.src_addr.call_id, callid_bitmap);
	RCU_INIT_POINTER(callid_sock[sock->proto.pptp.src_addr.call_id], NULL);
	spin_unlock(&chan_lock);
}