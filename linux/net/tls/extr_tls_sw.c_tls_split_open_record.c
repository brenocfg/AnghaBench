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
struct TYPE_2__ {scalar_t__ size; scalar_t__ end; scalar_t__ start; scalar_t__ copybreak; scalar_t__ curr; } ;
struct sk_msg {scalar_t__ apply_bytes; TYPE_1__ sg; } ;
struct tls_rec {struct sk_msg msg_plaintext; int /*<<< orphan*/  msg_encrypted; } ;
struct sock {int dummy; } ;
struct scatterlist {scalar_t__ length; scalar_t__ offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct scatterlist*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 
 int sk_msg_alloc (struct sock*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,scalar_t__) ; 
 int /*<<< orphan*/  sk_msg_iter_var_next (scalar_t__) ; 
 int /*<<< orphan*/  tls_free_rec (struct sock*,struct tls_rec*) ; 
 struct tls_rec* tls_get_rec (struct sock*) ; 

__attribute__((used)) static int tls_split_open_record(struct sock *sk, struct tls_rec *from,
				 struct tls_rec **to, struct sk_msg *msg_opl,
				 struct sk_msg *msg_oen, u32 split_point,
				 u32 tx_overhead_size, u32 *orig_end)
{
	u32 i, j, bytes = 0, apply = msg_opl->apply_bytes;
	struct scatterlist *sge, *osge, *nsge;
	u32 orig_size = msg_opl->sg.size;
	struct scatterlist tmp = { };
	struct sk_msg *msg_npl;
	struct tls_rec *new;
	int ret;

	new = tls_get_rec(sk);
	if (!new)
		return -ENOMEM;
	ret = sk_msg_alloc(sk, &new->msg_encrypted, msg_opl->sg.size +
			   tx_overhead_size, 0);
	if (ret < 0) {
		tls_free_rec(sk, new);
		return ret;
	}

	*orig_end = msg_opl->sg.end;
	i = msg_opl->sg.start;
	sge = sk_msg_elem(msg_opl, i);
	while (apply && sge->length) {
		if (sge->length > apply) {
			u32 len = sge->length - apply;

			get_page(sg_page(sge));
			sg_set_page(&tmp, sg_page(sge), len,
				    sge->offset + apply);
			sge->length = apply;
			bytes += apply;
			apply = 0;
		} else {
			apply -= sge->length;
			bytes += sge->length;
		}

		sk_msg_iter_var_next(i);
		if (i == msg_opl->sg.end)
			break;
		sge = sk_msg_elem(msg_opl, i);
	}

	msg_opl->sg.end = i;
	msg_opl->sg.curr = i;
	msg_opl->sg.copybreak = 0;
	msg_opl->apply_bytes = 0;
	msg_opl->sg.size = bytes;

	msg_npl = &new->msg_plaintext;
	msg_npl->apply_bytes = apply;
	msg_npl->sg.size = orig_size - bytes;

	j = msg_npl->sg.start;
	nsge = sk_msg_elem(msg_npl, j);
	if (tmp.length) {
		memcpy(nsge, &tmp, sizeof(*nsge));
		sk_msg_iter_var_next(j);
		nsge = sk_msg_elem(msg_npl, j);
	}

	osge = sk_msg_elem(msg_opl, i);
	while (osge->length) {
		memcpy(nsge, osge, sizeof(*nsge));
		sg_unmark_end(nsge);
		sk_msg_iter_var_next(i);
		sk_msg_iter_var_next(j);
		if (i == *orig_end)
			break;
		osge = sk_msg_elem(msg_opl, i);
		nsge = sk_msg_elem(msg_npl, j);
	}

	msg_npl->sg.end = j;
	msg_npl->sg.curr = j;
	msg_npl->sg.copybreak = 0;

	*to = new;
	return 0;
}