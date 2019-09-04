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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;
struct smap_psock {int /*<<< orphan*/  ingress; } ;
struct sk_msg_buff {int sg_start; int sg_end; int /*<<< orphan*/  list; TYPE_1__* sg_data; } ;
struct TYPE_2__ {int length; size_t offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int MAX_SKB_FRAGS ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  free_start_sg (struct sock*,struct sk_msg_buff*,int) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sk_msg_buff*) ; 
 struct sk_msg_buff* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sg_page (TYPE_1__*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,size_t) ; 
 int /*<<< orphan*/  sk_wmem_schedule (struct sock*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_tcp_ingress(struct sock *sk, int apply_bytes,
			   struct smap_psock *psock,
			   struct sk_msg_buff *md, int flags)
{
	bool apply = apply_bytes;
	size_t size, copied = 0;
	struct sk_msg_buff *r;
	int err = 0, i;

	r = kzalloc(sizeof(struct sk_msg_buff), __GFP_NOWARN | GFP_KERNEL);
	if (unlikely(!r))
		return -ENOMEM;

	lock_sock(sk);
	r->sg_start = md->sg_start;
	i = md->sg_start;

	do {
		size = (apply && apply_bytes < md->sg_data[i].length) ?
			apply_bytes : md->sg_data[i].length;

		if (!sk_wmem_schedule(sk, size)) {
			if (!copied)
				err = -ENOMEM;
			break;
		}

		sk_mem_charge(sk, size);
		r->sg_data[i] = md->sg_data[i];
		r->sg_data[i].length = size;
		md->sg_data[i].length -= size;
		md->sg_data[i].offset += size;
		copied += size;

		if (md->sg_data[i].length) {
			get_page(sg_page(&r->sg_data[i]));
			r->sg_end = (i + 1) == MAX_SKB_FRAGS ? 0 : i + 1;
		} else {
			i++;
			if (i == MAX_SKB_FRAGS)
				i = 0;
			r->sg_end = i;
		}

		if (apply) {
			apply_bytes -= size;
			if (!apply_bytes)
				break;
		}
	} while (i != md->sg_end);

	md->sg_start = i;

	if (!err) {
		list_add_tail(&r->list, &psock->ingress);
		sk->sk_data_ready(sk);
	} else {
		free_start_sg(sk, r, true);
		kfree(r);
	}

	release_sock(sk);
	return err;
}