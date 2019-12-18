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
struct sctp_endpoint {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  kfree (struct sctp_endpoint*) ; 
 struct sctp_endpoint* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_endpoint_init (struct sctp_endpoint*,struct sock*,int /*<<< orphan*/ ) ; 

struct sctp_endpoint *sctp_endpoint_new(struct sock *sk, gfp_t gfp)
{
	struct sctp_endpoint *ep;

	/* Build a local endpoint. */
	ep = kzalloc(sizeof(*ep), gfp);
	if (!ep)
		goto fail;

	if (!sctp_endpoint_init(ep, sk, gfp))
		goto fail_init;

	SCTP_DBG_OBJCNT_INC(ep);
	return ep;

fail_init:
	kfree(ep);
fail:
	return NULL;
}