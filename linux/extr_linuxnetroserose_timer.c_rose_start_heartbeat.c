#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct sock {TYPE_1__ sk_timer; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  rose_heartbeat_expiry ; 

void rose_start_heartbeat(struct sock *sk)
{
	del_timer(&sk->sk_timer);

	sk->sk_timer.function = rose_heartbeat_expiry;
	sk->sk_timer.expires  = jiffies + 5 * HZ;

	add_timer(&sk->sk_timer);
}