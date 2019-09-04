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
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfsd4_session {TYPE_1__ se_sessionid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_MAX_SESSIONID_LEN ; 
 int /*<<< orphan*/  xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_sessionid4(struct xdr_stream *xdr,
			      const struct nfsd4_session *session)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_MAX_SESSIONID_LEN);
	xdr_encode_opaque_fixed(p, session->se_sessionid.data,
					NFS4_MAX_SESSIONID_LEN);
}