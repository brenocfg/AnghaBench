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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct rose_sock {int condition; TYPE_1__* neighbour; int /*<<< orphan*/  state; int /*<<< orphan*/  vl; int /*<<< orphan*/  vs; int /*<<< orphan*/  vr; int /*<<< orphan*/  va; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int ROSE_CLEAR_CONFIRMATION ; 
#define  ROSE_CLEAR_REQUEST 130 
#define  ROSE_RESET_CONFIRMATION 129 
#define  ROSE_RESET_REQUEST 128 
 int /*<<< orphan*/  ROSE_STATE_3 ; 
 int /*<<< orphan*/  rose_disconnect (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rose_requeue_frames (struct sock*) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_start_idletimer (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int) ; 

__attribute__((used)) static int rose_state4_machine(struct sock *sk, struct sk_buff *skb, int frametype)
{
	struct rose_sock *rose = rose_sk(sk);

	switch (frametype) {
	case ROSE_RESET_REQUEST:
		rose_write_internal(sk, ROSE_RESET_CONFIRMATION);
		/* fall through */
	case ROSE_RESET_CONFIRMATION:
		rose_stop_timer(sk);
		rose_start_idletimer(sk);
		rose->condition = 0x00;
		rose->va        = 0;
		rose->vr        = 0;
		rose->vs        = 0;
		rose->vl        = 0;
		rose->state     = ROSE_STATE_3;
		rose_requeue_frames(sk);
		break;

	case ROSE_CLEAR_REQUEST:
		rose_write_internal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		rose->neighbour->use--;
		break;

	default:
		break;
	}

	return 0;
}