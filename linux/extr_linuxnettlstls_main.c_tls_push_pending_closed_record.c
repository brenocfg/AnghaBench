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
typedef  int /*<<< orphan*/  u16 ;
struct tls_context {int (* push_pending_record ) (struct sock*,int) ;struct scatterlist* partially_sent_record; int /*<<< orphan*/  partially_sent_offset; } ;
struct sock {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int stub1 (struct sock*,int) ; 
 int /*<<< orphan*/  tls_is_partially_sent_record (struct tls_context*) ; 
 int tls_push_sg (struct sock*,struct tls_context*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 

int tls_push_pending_closed_record(struct sock *sk, struct tls_context *ctx,
				   int flags, long *timeo)
{
	struct scatterlist *sg;
	u16 offset;

	if (!tls_is_partially_sent_record(ctx))
		return ctx->push_pending_record(sk, flags);

	sg = ctx->partially_sent_record;
	offset = ctx->partially_sent_offset;

	ctx->partially_sent_record = NULL;
	return tls_push_sg(sk, ctx, sg, offset, flags);
}