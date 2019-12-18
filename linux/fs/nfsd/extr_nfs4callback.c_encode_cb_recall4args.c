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
struct xdr_stream {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sc_file; int /*<<< orphan*/  sc_stateid; } ;
struct nfs4_delegation {TYPE_2__ dl_stid; } ;
struct nfs4_cb_compound_hdr {int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  fi_fhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CB_RECALL ; 
 int /*<<< orphan*/  encode_nfs_cb_opnum4 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs_fh4 (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_stateid4 (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_zero ; 

__attribute__((used)) static void encode_cb_recall4args(struct xdr_stream *xdr,
				  const struct nfs4_delegation *dp,
				  struct nfs4_cb_compound_hdr *hdr)
{
	__be32 *p;

	encode_nfs_cb_opnum4(xdr, OP_CB_RECALL);
	encode_stateid4(xdr, &dp->dl_stid.sc_stateid);

	p = xdr_reserve_space(xdr, 4);
	*p++ = xdr_zero;			/* truncate */

	encode_nfs_fh4(xdr, &dp->dl_stid.sc_file->fi_fhandle);

	hdr->nops++;
}