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
struct sk_buff {int* data; } ;
struct rose_sock {TYPE_1__* neighbour; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
#define  ROSE_CLEAR_CONFIRMATION 129 
#define  ROSE_CLEAR_REQUEST 128 
 int /*<<< orphan*/  rose_disconnect (struct sock*,int /*<<< orphan*/ ,int,int) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int) ; 

__attribute__((used)) static int rose_state2_machine(struct sock *sk, struct sk_buff *skb, int frametype)
{
	struct rose_sock *rose = rose_sk(sk);

	switch (frametype) {
	case ROSE_CLEAR_REQUEST:
		rose_write_internal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		rose->neighbour->use--;
		break;

	case ROSE_CLEAR_CONFIRMATION:
		rose_disconnect(sk, 0, -1, -1);
		rose->neighbour->use--;
		break;

	default:
		break;
	}

	return 0;
}