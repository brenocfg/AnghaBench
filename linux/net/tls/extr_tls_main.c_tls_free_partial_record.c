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
struct tls_context {struct scatterlist* partially_sent_record; } ;
struct sock {int dummy; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int /*<<< orphan*/ ) ; 

bool tls_free_partial_record(struct sock *sk, struct tls_context *ctx)
{
	struct scatterlist *sg;

	sg = ctx->partially_sent_record;
	if (!sg)
		return false;

	while (1) {
		put_page(sg_page(sg));
		sk_mem_uncharge(sk, sg->length);

		if (sg_is_last(sg))
			break;
		sg++;
	}
	ctx->partially_sent_record = NULL;
	return true;
}