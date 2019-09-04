#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xdr_netobj {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct xdr_buf {int dummy; } ;
struct TYPE_3__ {TYPE_2__* head; } ;
struct svc_rqst {TYPE_1__ rq_res; } ;
struct kvec {int iov_len; void** iov_base; } ;
struct gss_ctx {int dummy; } ;
typedef  void* __be32 ;
struct TYPE_4__ {int iov_len; void** iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  RPC_AUTH_GSS ; 
 int /*<<< orphan*/  XDR_QUADLEN (int) ; 
 scalar_t__ gss_get_mic (struct gss_ctx*,struct xdr_buf*,struct xdr_netobj*) ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void** kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int round_up_to_quad (int) ; 
 int /*<<< orphan*/  svc_putnl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_buf_from_iov (struct kvec*,struct xdr_buf*) ; 
 int /*<<< orphan*/  xdr_ressize_check (struct svc_rqst*,void**) ; 

__attribute__((used)) static int
gss_write_verf(struct svc_rqst *rqstp, struct gss_ctx *ctx_id, u32 seq)
{
	__be32			*xdr_seq;
	u32			maj_stat;
	struct xdr_buf		verf_data;
	struct xdr_netobj	mic;
	__be32			*p;
	struct kvec		iov;
	int err = -1;

	svc_putnl(rqstp->rq_res.head, RPC_AUTH_GSS);
	xdr_seq = kmalloc(4, GFP_KERNEL);
	if (!xdr_seq)
		return -1;
	*xdr_seq = htonl(seq);

	iov.iov_base = xdr_seq;
	iov.iov_len = 4;
	xdr_buf_from_iov(&iov, &verf_data);
	p = rqstp->rq_res.head->iov_base + rqstp->rq_res.head->iov_len;
	mic.data = (u8 *)(p + 1);
	maj_stat = gss_get_mic(ctx_id, &verf_data, &mic);
	if (maj_stat != GSS_S_COMPLETE)
		goto out;
	*p++ = htonl(mic.len);
	memset((u8 *)p + mic.len, 0, round_up_to_quad(mic.len) - mic.len);
	p += XDR_QUADLEN(mic.len);
	if (!xdr_ressize_check(rqstp, p))
		goto out;
	err = 0;
out:
	kfree(xdr_seq);
	return err;
}