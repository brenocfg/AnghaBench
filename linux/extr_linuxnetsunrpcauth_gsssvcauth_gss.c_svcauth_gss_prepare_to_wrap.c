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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_buf {TYPE_1__* head; } ;
struct gss_svc_data {scalar_t__* verf_start; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ rpc_success ; 

__attribute__((used)) static __be32 *
svcauth_gss_prepare_to_wrap(struct xdr_buf *resbuf, struct gss_svc_data *gsd)
{
	__be32 *p;
	u32 verf_len;

	p = gsd->verf_start;
	gsd->verf_start = NULL;

	/* If the reply stat is nonzero, don't wrap: */
	if (*(p-1) != rpc_success)
		return NULL;
	/* Skip the verifier: */
	p += 1;
	verf_len = ntohl(*p++);
	p += XDR_QUADLEN(verf_len);
	/* move accept_stat to right place: */
	memcpy(p, p + 2, 4);
	/* Also don't wrap if the accept stat is nonzero: */
	if (*p != rpc_success) {
		resbuf->head[0].iov_len -= 2 * 4;
		return NULL;
	}
	p++;
	return p;
}