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
struct TYPE_4__ {int code_set; int designator_type; int /*<<< orphan*/  pr_key; int /*<<< orphan*/  designator_len; int /*<<< orphan*/  designator; } ;
struct TYPE_3__ {int /*<<< orphan*/  sig_len; int /*<<< orphan*/  sig; int /*<<< orphan*/  offset; } ;
struct pnfs_block_volume {int type; TYPE_2__ scsi; TYPE_1__ simple; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOTSUPP ; 
 int ETOOSMALL ; 
#define  PNFS_BLOCK_VOLUME_SCSI 129 
#define  PNFS_BLOCK_VOLUME_SIMPLE 128 
 int XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static int
nfsd4_block_encode_volume(struct xdr_stream *xdr, struct pnfs_block_volume *b)
{
	__be32 *p;
	int len;

	switch (b->type) {
	case PNFS_BLOCK_VOLUME_SIMPLE:
		len = 4 + 4 + 8 + 4 + (XDR_QUADLEN(b->simple.sig_len) << 2);
		p = xdr_reserve_space(xdr, len);
		if (!p)
			return -ETOOSMALL;

		*p++ = cpu_to_be32(b->type);
		*p++ = cpu_to_be32(1);	/* single signature */
		p = xdr_encode_hyper(p, b->simple.offset);
		p = xdr_encode_opaque(p, b->simple.sig, b->simple.sig_len);
		break;
	case PNFS_BLOCK_VOLUME_SCSI:
		len = 4 + 4 + 4 + 4 + (XDR_QUADLEN(b->scsi.designator_len) << 2) + 8;
		p = xdr_reserve_space(xdr, len);
		if (!p)
			return -ETOOSMALL;

		*p++ = cpu_to_be32(b->type);
		*p++ = cpu_to_be32(b->scsi.code_set);
		*p++ = cpu_to_be32(b->scsi.designator_type);
		p = xdr_encode_opaque(p, b->scsi.designator, b->scsi.designator_len);
		p = xdr_encode_hyper(p, b->scsi.pr_key);
		break;
	default:
		return -ENOTSUPP;
	}

	return len;
}