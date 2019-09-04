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
struct xdr_stream {int dummy; } ;
struct gssx_status {int /*<<< orphan*/  options; int /*<<< orphan*/  server_ctx; int /*<<< orphan*/  minor_status_string; int /*<<< orphan*/  major_status_string; int /*<<< orphan*/  minor_status; int /*<<< orphan*/  mech; int /*<<< orphan*/  major_status; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOSPC ; 
 int dummy_dec_opt_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int gssx_dec_status(struct xdr_stream *xdr,
			   struct gssx_status *status)
{
	__be32 *p;
	int err;

	/* status->major_status */
	p = xdr_inline_decode(xdr, 8);
	if (unlikely(p == NULL))
		return -ENOSPC;
	p = xdr_decode_hyper(p, &status->major_status);

	/* status->mech */
	err = gssx_dec_buffer(xdr, &status->mech);
	if (err)
		return err;

	/* status->minor_status */
	p = xdr_inline_decode(xdr, 8);
	if (unlikely(p == NULL))
		return -ENOSPC;
	p = xdr_decode_hyper(p, &status->minor_status);

	/* status->major_status_string */
	err = gssx_dec_buffer(xdr, &status->major_status_string);
	if (err)
		return err;

	/* status->minor_status_string */
	err = gssx_dec_buffer(xdr, &status->minor_status_string);
	if (err)
		return err;

	/* status->server_ctx */
	err = gssx_dec_buffer(xdr, &status->server_ctx);
	if (err)
		return err;

	/* we assume we have no options for now, so simply consume them */
	/* status->options */
	err = dummy_dec_opt_array(xdr, &status->options);

	return err;
}