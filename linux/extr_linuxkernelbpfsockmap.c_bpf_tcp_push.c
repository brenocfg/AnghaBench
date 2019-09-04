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
struct sock {int dummy; } ;
struct sk_msg_buff {int sg_start; scalar_t__ sg_end; struct scatterlist* sg_data; } ;
struct scatterlist {int length; int offset; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_SKB_FRAGS ; 
 int do_tcp_sendpages (struct sock*,struct page*,int,size_t,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_rate_check_app_limited (struct sock*) ; 

__attribute__((used)) static int bpf_tcp_push(struct sock *sk, int apply_bytes,
			struct sk_msg_buff *md,
			int flags, bool uncharge)
{
	bool apply = apply_bytes;
	struct scatterlist *sg;
	int offset, ret = 0;
	struct page *p;
	size_t size;

	while (1) {
		sg = md->sg_data + md->sg_start;
		size = (apply && apply_bytes < sg->length) ?
			apply_bytes : sg->length;
		offset = sg->offset;

		tcp_rate_check_app_limited(sk);
		p = sg_page(sg);
retry:
		ret = do_tcp_sendpages(sk, p, offset, size, flags);
		if (ret != size) {
			if (ret > 0) {
				if (apply)
					apply_bytes -= ret;

				sg->offset += ret;
				sg->length -= ret;
				size -= ret;
				offset += ret;
				if (uncharge)
					sk_mem_uncharge(sk, ret);
				goto retry;
			}

			return ret;
		}

		if (apply)
			apply_bytes -= ret;
		sg->offset += ret;
		sg->length -= ret;
		if (uncharge)
			sk_mem_uncharge(sk, ret);

		if (!sg->length) {
			put_page(p);
			md->sg_start++;
			if (md->sg_start == MAX_SKB_FRAGS)
				md->sg_start = 0;
			sg_init_table(sg, 1);

			if (md->sg_start == md->sg_end)
				break;
		}

		if (apply && !apply_bytes)
			break;
	}
	return 0;
}