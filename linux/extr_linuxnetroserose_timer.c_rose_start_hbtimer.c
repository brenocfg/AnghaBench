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
struct sock {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct rose_sock {TYPE_1__ timer; scalar_t__ hb; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_timer_expiry ; 

void rose_start_hbtimer(struct sock *sk)
{
	struct rose_sock *rose = rose_sk(sk);

	del_timer(&rose->timer);

	rose->timer.function = rose_timer_expiry;
	rose->timer.expires  = jiffies + rose->hb;

	add_timer(&rose->timer);
}