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
struct sock {int sk_route_caps; } ;
struct sk_msg_buff {int sg_curr; int sg_end; scalar_t__ sg_copybreak; struct scatterlist* sg_data; } ;
struct scatterlist {scalar_t__ length; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOSPC ; 
 int MAX_SKB_FRAGS ; 
 int NETIF_F_NOCACHE_COPY ; 
 int copy_from_iter (char*,int,struct iov_iter*) ; 
 int copy_from_iter_nocache (char*,int,struct iov_iter*) ; 
 char* sg_virt (struct scatterlist*) ; 

__attribute__((used)) static int memcopy_from_iter(struct sock *sk,
			     struct sk_msg_buff *md,
			     struct iov_iter *from, int bytes)
{
	struct scatterlist *sg = md->sg_data;
	int i = md->sg_curr, rc = -ENOSPC;

	do {
		int copy;
		char *to;

		if (md->sg_copybreak >= sg[i].length) {
			md->sg_copybreak = 0;

			if (++i == MAX_SKB_FRAGS)
				i = 0;

			if (i == md->sg_end)
				break;
		}

		copy = sg[i].length - md->sg_copybreak;
		to = sg_virt(&sg[i]) + md->sg_copybreak;
		md->sg_copybreak += copy;

		if (sk->sk_route_caps & NETIF_F_NOCACHE_COPY)
			rc = copy_from_iter_nocache(to, copy, from);
		else
			rc = copy_from_iter(to, copy, from);

		if (rc != copy) {
			rc = -EFAULT;
			goto out;
		}

		bytes -= copy;
		if (!bytes)
			break;

		md->sg_copybreak = 0;
		if (++i == MAX_SKB_FRAGS)
			i = 0;
	} while (i != md->sg_end);
out:
	md->sg_curr = i;
	return rc;
}