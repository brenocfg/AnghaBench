#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct nfs42_layoutstat_devinfo {TYPE_3__ ld_private; int /*<<< orphan*/  layout_type; TYPE_1__ dev_id; int /*<<< orphan*/  write_bytes; int /*<<< orphan*/  write_count; int /*<<< orphan*/  read_bytes; int /*<<< orphan*/  read_count; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct nfs42_layoutstat_args {int /*<<< orphan*/  stateid; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* encode ) (struct xdr_stream*,struct nfs42_layoutstat_args const*,TYPE_3__*) ;} ;

/* Variables and functions */
 int NFS4_DEVICEID4_SIZE ; 
 int /*<<< orphan*/  OP_LAYOUTSTATS ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_layoutstats_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  stub1 (struct xdr_stream*,struct nfs42_layoutstat_args const*,TYPE_3__*) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void encode_layoutstats(struct xdr_stream *xdr,
			       const struct nfs42_layoutstat_args *args,
			       struct nfs42_layoutstat_devinfo *devinfo,
			       struct compound_hdr *hdr)
{
	__be32 *p;

	encode_op_hdr(xdr, OP_LAYOUTSTATS, decode_layoutstats_maxsz, hdr);
	p = reserve_space(xdr, 8 + 8);
	p = xdr_encode_hyper(p, devinfo->offset);
	p = xdr_encode_hyper(p, devinfo->length);
	encode_nfs4_stateid(xdr, &args->stateid);
	p = reserve_space(xdr, 4*8 + NFS4_DEVICEID4_SIZE + 4);
	p = xdr_encode_hyper(p, devinfo->read_count);
	p = xdr_encode_hyper(p, devinfo->read_bytes);
	p = xdr_encode_hyper(p, devinfo->write_count);
	p = xdr_encode_hyper(p, devinfo->write_bytes);
	p = xdr_encode_opaque_fixed(p, devinfo->dev_id.data,
			NFS4_DEVICEID4_SIZE);
	/* Encode layoutupdate4 */
	*p++ = cpu_to_be32(devinfo->layout_type);
	if (devinfo->ld_private.ops)
		devinfo->ld_private.ops->encode(xdr, args,
				&devinfo->ld_private);
	else
		encode_uint32(xdr, 0);
}