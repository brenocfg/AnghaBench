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
typedef  int u16 ;
struct tls_context {int in_tcp_sendpages; int partially_sent_offset; void* partially_sent_record; } ;
struct sock {int dummy; } ;
struct scatterlist {int length; int offset; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int MSG_SENDPAGE_NOTLAST ; 
 int do_tcp_sendpages (struct sock*,struct page*,int,size_t,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_rate_check_app_limited (struct sock*) ; 

int tls_push_sg(struct sock *sk,
		struct tls_context *ctx,
		struct scatterlist *sg,
		u16 first_offset,
		int flags)
{
	int sendpage_flags = flags | MSG_SENDPAGE_NOTLAST;
	int ret = 0;
	struct page *p;
	size_t size;
	int offset = first_offset;

	size = sg->length - offset;
	offset += sg->offset;

	ctx->in_tcp_sendpages = true;
	while (1) {
		if (sg_is_last(sg))
			sendpage_flags = flags;

		/* is sending application-limited? */
		tcp_rate_check_app_limited(sk);
		p = sg_page(sg);
retry:
		ret = do_tcp_sendpages(sk, p, offset, size, sendpage_flags);

		if (ret != size) {
			if (ret > 0) {
				offset += ret;
				size -= ret;
				goto retry;
			}

			offset -= sg->offset;
			ctx->partially_sent_offset = offset;
			ctx->partially_sent_record = (void *)sg;
			ctx->in_tcp_sendpages = false;
			return ret;
		}

		put_page(p);
		sk_mem_uncharge(sk, sg->length);
		sg = sg_next(sg);
		if (!sg)
			break;

		offset = sg->offset;
		size = sg->length;
	}

	ctx->in_tcp_sendpages = false;

	return 0;
}