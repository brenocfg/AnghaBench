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
typedef  int time64_t ;
struct afs_net {int /*<<< orphan*/  fs_timer; scalar_t__ live; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  afs_dec_servers_outstanding (struct afs_net*) ; 
 int /*<<< orphan*/  afs_inc_servers_outstanding (struct afs_net*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ timer_reduce (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void afs_set_server_timer(struct afs_net *net, time64_t delay)
{
	if (net->live) {
		afs_inc_servers_outstanding(net);
		if (timer_reduce(&net->fs_timer, jiffies + delay * HZ))
			afs_dec_servers_outstanding(net);
	}
}