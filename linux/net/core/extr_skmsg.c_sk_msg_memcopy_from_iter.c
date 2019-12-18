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
typedef  int u32 ;
struct sock {int sk_route_caps; } ;
struct TYPE_2__ {int curr; int end; scalar_t__ copybreak; } ;
struct sk_msg {TYPE_1__ sg; } ;
struct scatterlist {scalar_t__ length; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOSPC ; 
 int NETIF_F_NOCACHE_COPY ; 
 int copy_from_iter (void*,int,struct iov_iter*) ; 
 int copy_from_iter_nocache (void*,int,struct iov_iter*) ; 
 void* sg_virt (struct scatterlist*) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,int) ; 
 int /*<<< orphan*/  sk_msg_iter_var_next (int) ; 

int sk_msg_memcopy_from_iter(struct sock *sk, struct iov_iter *from,
			     struct sk_msg *msg, u32 bytes)
{
	int ret = -ENOSPC, i = msg->sg.curr;
	struct scatterlist *sge;
	u32 copy, buf_size;
	void *to;

	do {
		sge = sk_msg_elem(msg, i);
		/* This is possible if a trim operation shrunk the buffer */
		if (msg->sg.copybreak >= sge->length) {
			msg->sg.copybreak = 0;
			sk_msg_iter_var_next(i);
			if (i == msg->sg.end)
				break;
			sge = sk_msg_elem(msg, i);
		}

		buf_size = sge->length - msg->sg.copybreak;
		copy = (buf_size > bytes) ? bytes : buf_size;
		to = sg_virt(sge) + msg->sg.copybreak;
		msg->sg.copybreak += copy;
		if (sk->sk_route_caps & NETIF_F_NOCACHE_COPY)
			ret = copy_from_iter_nocache(to, copy, from);
		else
			ret = copy_from_iter(to, copy, from);
		if (ret != copy) {
			ret = -EFAULT;
			goto out;
		}
		bytes -= copy;
		if (!bytes)
			break;
		msg->sg.copybreak = 0;
		sk_msg_iter_var_next(i);
	} while (i != msg->sg.end);
out:
	msg->sg.curr = i;
	return ret;
}