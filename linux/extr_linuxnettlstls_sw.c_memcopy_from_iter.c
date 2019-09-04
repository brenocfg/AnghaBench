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
struct tls_sw_context_tx {int sg_plaintext_num_elem; struct scatterlist* sg_plaintext_data; } ;
struct tls_context {int pending_open_record_frags; } ;
struct sock {int dummy; } ;
struct scatterlist {int length; scalar_t__ offset; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int copy_from_iter (scalar_t__,int,struct iov_iter*) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static int memcopy_from_iter(struct sock *sk, struct iov_iter *from,
			     int bytes)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	struct scatterlist *sg = ctx->sg_plaintext_data;
	int copy, i, rc = 0;

	for (i = tls_ctx->pending_open_record_frags;
	     i < ctx->sg_plaintext_num_elem; ++i) {
		copy = sg[i].length;
		if (copy_from_iter(
				page_address(sg_page(&sg[i])) + sg[i].offset,
				copy, from) != copy) {
			rc = -EFAULT;
			goto out;
		}
		bytes -= copy;

		++tls_ctx->pending_open_record_frags;

		if (!bytes)
			break;
	}

out:
	return rc;
}