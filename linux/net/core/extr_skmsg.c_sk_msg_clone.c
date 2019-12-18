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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct TYPE_2__ {int start; int end; int /*<<< orphan*/  size; } ;
struct sk_msg {TYPE_1__ sg; } ;
struct scatterlist {scalar_t__ length; scalar_t__ offset; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ sg_page (struct scatterlist*) ; 
 scalar_t__ sg_virt (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,scalar_t__) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,int) ; 
 int /*<<< orphan*/  sk_msg_full (struct sk_msg*) ; 
 int /*<<< orphan*/  sk_msg_iter_var_next (int) ; 
 int /*<<< orphan*/  sk_msg_page_add (struct sk_msg*,scalar_t__,scalar_t__,scalar_t__) ; 

int sk_msg_clone(struct sock *sk, struct sk_msg *dst, struct sk_msg *src,
		 u32 off, u32 len)
{
	int i = src->sg.start;
	struct scatterlist *sge = sk_msg_elem(src, i);
	struct scatterlist *sgd = NULL;
	u32 sge_len, sge_off;

	while (off) {
		if (sge->length > off)
			break;
		off -= sge->length;
		sk_msg_iter_var_next(i);
		if (i == src->sg.end && off)
			return -ENOSPC;
		sge = sk_msg_elem(src, i);
	}

	while (len) {
		sge_len = sge->length - off;
		if (sge_len > len)
			sge_len = len;

		if (dst->sg.end)
			sgd = sk_msg_elem(dst, dst->sg.end - 1);

		if (sgd &&
		    (sg_page(sge) == sg_page(sgd)) &&
		    (sg_virt(sge) + off == sg_virt(sgd) + sgd->length)) {
			sgd->length += sge_len;
			dst->sg.size += sge_len;
		} else if (!sk_msg_full(dst)) {
			sge_off = sge->offset + off;
			sk_msg_page_add(dst, sg_page(sge), sge_len, sge_off);
		} else {
			return -ENOSPC;
		}

		off = 0;
		len -= sge_len;
		sk_mem_charge(sk, sge_len);
		sk_msg_iter_var_next(i);
		if (i == src->sg.end && len)
			return -ENOSPC;
		sge = sk_msg_elem(src, i);
	}

	return 0;
}