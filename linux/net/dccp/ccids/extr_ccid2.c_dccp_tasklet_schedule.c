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
struct tasklet_struct {int /*<<< orphan*/  state; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {struct tasklet_struct dccps_xmitlet; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASKLET_STATE_SCHED ; 
 int /*<<< orphan*/  __tasklet_schedule (struct tasklet_struct*) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dccp_tasklet_schedule(struct sock *sk)
{
	struct tasklet_struct *t = &dccp_sk(sk)->dccps_xmitlet;

	if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state)) {
		sock_hold(sk);
		__tasklet_schedule(t);
	}
}