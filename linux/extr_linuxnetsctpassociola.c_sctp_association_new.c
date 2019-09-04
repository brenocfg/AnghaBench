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
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum sctp_scope { ____Placeholder_sctp_scope } sctp_scope ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assoc ; 
 int /*<<< orphan*/  kfree (struct sctp_association*) ; 
 struct sctp_association* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_association_init (struct sctp_association*,struct sctp_endpoint const*,struct sock const*,int,int /*<<< orphan*/ ) ; 

struct sctp_association *sctp_association_new(const struct sctp_endpoint *ep,
					      const struct sock *sk,
					      enum sctp_scope scope, gfp_t gfp)
{
	struct sctp_association *asoc;

	asoc = kzalloc(sizeof(*asoc), gfp);
	if (!asoc)
		goto fail;

	if (!sctp_association_init(asoc, ep, sk, scope, gfp))
		goto fail_init;

	SCTP_DBG_OBJCNT_INC(assoc);

	pr_debug("Created asoc %p\n", asoc);

	return asoc;

fail_init:
	kfree(asoc);
fail:
	return NULL;
}