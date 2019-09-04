#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__* neighbour; } ;
struct TYPE_3__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROSE_CLEAR_CONFIRMATION ; 
 int ROSE_CLEAR_REQUEST ; 
 int /*<<< orphan*/  rose_disconnect (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rose_state5_machine(struct sock *sk, struct sk_buff *skb, int frametype)
{
	if (frametype == ROSE_CLEAR_REQUEST) {
		rose_write_internal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		rose_sk(sk)->neighbour->use--;
	}

	return 0;
}