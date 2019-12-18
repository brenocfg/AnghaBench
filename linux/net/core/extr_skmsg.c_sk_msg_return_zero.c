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
struct TYPE_2__ {int start; int end; } ;
struct sk_msg {TYPE_1__ sg; } ;
struct scatterlist {int length; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,int) ; 
 int /*<<< orphan*/  sk_msg_iter_var_next (int) ; 

void sk_msg_return_zero(struct sock *sk, struct sk_msg *msg, int bytes)
{
	int i = msg->sg.start;

	do {
		struct scatterlist *sge = sk_msg_elem(msg, i);

		if (bytes < sge->length) {
			sge->length -= bytes;
			sge->offset += bytes;
			sk_mem_uncharge(sk, bytes);
			break;
		}

		sk_mem_uncharge(sk, sge->length);
		bytes -= sge->length;
		sge->length = 0;
		sge->offset = 0;
		sk_msg_iter_var_next(i);
	} while (bytes && i != msg->sg.end);
	msg->sg.start = i;
}