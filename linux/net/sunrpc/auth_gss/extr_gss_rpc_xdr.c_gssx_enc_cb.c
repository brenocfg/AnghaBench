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
struct gssx_cb {int /*<<< orphan*/  application_data; int /*<<< orphan*/  acceptor_address; int /*<<< orphan*/  acceptor_addrtype; int /*<<< orphan*/  initiator_address; int /*<<< orphan*/  initiator_addrtype; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOSPC ; 
 int gssx_enc_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static int gssx_enc_cb(struct xdr_stream *xdr, struct gssx_cb *cb)
{
	__be32 *p;
	int err;

	/* cb->initiator_addrtype */
	p = xdr_reserve_space(xdr, 8);
	if (!p)
		return -ENOSPC;
	p = xdr_encode_hyper(p, cb->initiator_addrtype);

	/* cb->initiator_address */
	err = gssx_enc_buffer(xdr, &cb->initiator_address);
	if (err)
		return err;

	/* cb->acceptor_addrtype */
	p = xdr_reserve_space(xdr, 8);
	if (!p)
		return -ENOSPC;
	p = xdr_encode_hyper(p, cb->acceptor_addrtype);

	/* cb->acceptor_address */
	err = gssx_enc_buffer(xdr, &cb->acceptor_address);
	if (err)
		return err;

	/* cb->application_data */
	err = gssx_enc_buffer(xdr, &cb->application_data);

	return err;
}