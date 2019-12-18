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
typedef  int u32 ;
struct xdr_netobj {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct xdr_buf {int len; int /*<<< orphan*/ * head; } ;
struct svc_rqst {scalar_t__ rq_deferred; int /*<<< orphan*/  rq_flags; } ;
struct gss_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GSS_S_COMPLETE ; 
 scalar_t__ RPC_MAX_AUTH_SIZE ; 
 int /*<<< orphan*/  RQ_SPLICE_OK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gss_verify_mic (struct gss_ctx*,struct xdr_buf*,struct xdr_netobj*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ read_bytes_from_xdr_buf (struct xdr_buf*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ read_u32_from_xdr_buf (struct xdr_buf*,int,scalar_t__*) ; 
 scalar_t__ round_up_to_quad (scalar_t__) ; 
 int svc_getnl (int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_buf_subsegment (struct xdr_buf*,struct xdr_buf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
unwrap_integ_data(struct svc_rqst *rqstp, struct xdr_buf *buf, u32 seq, struct gss_ctx *ctx)
{
	int stat = -EINVAL;
	u32 integ_len, maj_stat;
	struct xdr_netobj mic;
	struct xdr_buf integ_buf;

	/* NFS READ normally uses splice to send data in-place. However
	 * the data in cache can change after the reply's MIC is computed
	 * but before the RPC reply is sent. To prevent the client from
	 * rejecting the server-computed MIC in this somewhat rare case,
	 * do not use splice with the GSS integrity service.
	 */
	clear_bit(RQ_SPLICE_OK, &rqstp->rq_flags);

	/* Did we already verify the signature on the original pass through? */
	if (rqstp->rq_deferred)
		return 0;

	integ_len = svc_getnl(&buf->head[0]);
	if (integ_len & 3)
		return stat;
	if (integ_len > buf->len)
		return stat;
	if (xdr_buf_subsegment(buf, &integ_buf, 0, integ_len)) {
		WARN_ON_ONCE(1);
		return stat;
	}
	/* copy out mic... */
	if (read_u32_from_xdr_buf(buf, integ_len, &mic.len))
		return stat;
	if (mic.len > RPC_MAX_AUTH_SIZE)
		return stat;
	mic.data = kmalloc(mic.len, GFP_KERNEL);
	if (!mic.data)
		return stat;
	if (read_bytes_from_xdr_buf(buf, integ_len + 4, mic.data, mic.len))
		goto out;
	maj_stat = gss_verify_mic(ctx, &integ_buf, &mic);
	if (maj_stat != GSS_S_COMPLETE)
		goto out;
	if (svc_getnl(&buf->head[0]) != seq)
		goto out;
	/* trim off the mic and padding at the end before returning */
	buf->len -= 4 + round_up_to_quad(mic.len);
	stat = 0;
out:
	kfree(mic.data);
	return stat;
}