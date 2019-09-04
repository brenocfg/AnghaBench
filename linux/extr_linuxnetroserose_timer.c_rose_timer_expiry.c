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
struct timer_list {int dummy; } ;
struct sock {int dummy; } ;
struct rose_sock {int state; int condition; TYPE_1__* neighbour; struct sock sock; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  ROSE_CLEAR_REQUEST ; 
 int ROSE_COND_ACK_PENDING ; 
#define  ROSE_STATE_1 131 
#define  ROSE_STATE_2 130 
#define  ROSE_STATE_3 129 
#define  ROSE_STATE_4 128 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct rose_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct rose_sock* rose ; 
 int /*<<< orphan*/  rose_disconnect (struct sock*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rose_enquiry_response (struct sock*) ; 
 int /*<<< orphan*/  rose_start_t3timer (struct sock*) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void rose_timer_expiry(struct timer_list *t)
{
	struct rose_sock *rose = from_timer(rose, t, timer);
	struct sock *sk = &rose->sock;

	bh_lock_sock(sk);
	switch (rose->state) {
	case ROSE_STATE_1:	/* T1 */
	case ROSE_STATE_4:	/* T2 */
		rose_write_internal(sk, ROSE_CLEAR_REQUEST);
		rose->state = ROSE_STATE_2;
		rose_start_t3timer(sk);
		break;

	case ROSE_STATE_2:	/* T3 */
		rose->neighbour->use--;
		rose_disconnect(sk, ETIMEDOUT, -1, -1);
		break;

	case ROSE_STATE_3:	/* HB */
		if (rose->condition & ROSE_COND_ACK_PENDING) {
			rose->condition &= ~ROSE_COND_ACK_PENDING;
			rose_enquiry_response(sk);
		}
		break;
	}
	bh_unlock_sock(sk);
}