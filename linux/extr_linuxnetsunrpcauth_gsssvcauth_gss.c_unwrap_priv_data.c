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
typedef  int u32 ;
struct xdr_buf {int len; TYPE_1__* head; int /*<<< orphan*/  buflen; } ;
struct svc_rqst {scalar_t__ rq_deferred; int /*<<< orphan*/  rq_flags; } ;
struct gss_ctx {int dummy; } ;
struct TYPE_2__ {int iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int GSS_S_COMPLETE ; 
 int /*<<< orphan*/  RPCSVC_MAXPAYLOAD ; 
 int /*<<< orphan*/  RQ_SPLICE_OK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fix_priv_head (struct xdr_buf*,int) ; 
 int gss_unwrap (struct gss_ctx*,int /*<<< orphan*/ ,struct xdr_buf*) ; 
 int svc_getnl (TYPE_1__*) ; 
 int total_buf_len (struct xdr_buf*) ; 
 int /*<<< orphan*/  xdr_shift_buf (struct xdr_buf*,int) ; 

__attribute__((used)) static int
unwrap_priv_data(struct svc_rqst *rqstp, struct xdr_buf *buf, u32 seq, struct gss_ctx *ctx)
{
	u32 priv_len, maj_stat;
	int pad, saved_len, remaining_len, offset;

	clear_bit(RQ_SPLICE_OK, &rqstp->rq_flags);

	priv_len = svc_getnl(&buf->head[0]);
	if (rqstp->rq_deferred) {
		/* Already decrypted last time through! The sequence number
		 * check at out_seq is unnecessary but harmless: */
		goto out_seq;
	}
	/* buf->len is the number of bytes from the original start of the
	 * request to the end, where head[0].iov_len is just the bytes
	 * not yet read from the head, so these two values are different: */
	remaining_len = total_buf_len(buf);
	if (priv_len > remaining_len)
		return -EINVAL;
	pad = remaining_len - priv_len;
	buf->len -= pad;
	fix_priv_head(buf, pad);

	/* Maybe it would be better to give gss_unwrap a length parameter: */
	saved_len = buf->len;
	buf->len = priv_len;
	maj_stat = gss_unwrap(ctx, 0, buf);
	pad = priv_len - buf->len;
	buf->len = saved_len;
	buf->len -= pad;
	/* The upper layers assume the buffer is aligned on 4-byte boundaries.
	 * In the krb5p case, at least, the data ends up offset, so we need to
	 * move it around. */
	/* XXX: This is very inefficient.  It would be better to either do
	 * this while we encrypt, or maybe in the receive code, if we can peak
	 * ahead and work out the service and mechanism there. */
	offset = buf->head[0].iov_len % 4;
	if (offset) {
		buf->buflen = RPCSVC_MAXPAYLOAD;
		xdr_shift_buf(buf, offset);
		fix_priv_head(buf, pad);
	}
	if (maj_stat != GSS_S_COMPLETE)
		return -EINVAL;
out_seq:
	if (svc_getnl(&buf->head[0]) != seq)
		return -EINVAL;
	return 0;
}