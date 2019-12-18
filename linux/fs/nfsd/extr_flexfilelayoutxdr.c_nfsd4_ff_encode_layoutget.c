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
struct TYPE_4__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int si_generation; int /*<<< orphan*/  si_opaque; } ;
struct pnfs_ff_layout {int flags; TYPE_2__ fh; TYPE_1__ stateid; int /*<<< orphan*/  deviceid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct nfsd4_layoutget {struct pnfs_ff_layout* lg_content; } ;
struct nfsd4_deviceid {int dummy; } ;
struct ff_idmap {int len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  stateid_opaque_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  nfserr_toosmall ; 
 void* sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__be32
nfsd4_ff_encode_layoutget(struct xdr_stream *xdr,
		struct nfsd4_layoutget *lgp)
{
	struct pnfs_ff_layout *fl = lgp->lg_content;
	int len, mirror_len, ds_len, fh_len;
	__be32 *p;

	/*
	 * Unlike nfsd4_encode_user, we know these will
	 * always be stringified.
	 */
	struct ff_idmap uid;
	struct ff_idmap gid;

	fh_len = 4 + fl->fh.size;

	uid.len = sprintf(uid.buf, "%u", from_kuid(&init_user_ns, fl->uid));
	gid.len = sprintf(gid.buf, "%u", from_kgid(&init_user_ns, fl->gid));

	/* 8 + len for recording the length, name, and padding */
	ds_len = 20 + sizeof(stateid_opaque_t) + 4 + fh_len +
		 8 + uid.len + 8 + gid.len;

	mirror_len = 4 + ds_len;

	/* The layout segment */
	len = 20 + mirror_len;

	p = xdr_reserve_space(xdr, sizeof(__be32) + len);
	if (!p)
		return nfserr_toosmall;

	*p++ = cpu_to_be32(len);
	p = xdr_encode_hyper(p, 0);		/* stripe unit of 1 */

	*p++ = cpu_to_be32(1);			/* single mirror */
	*p++ = cpu_to_be32(1);			/* single data server */

	p = xdr_encode_opaque_fixed(p, &fl->deviceid,
			sizeof(struct nfsd4_deviceid));

	*p++ = cpu_to_be32(1);			/* efficiency */

	*p++ = cpu_to_be32(fl->stateid.si_generation);
	p = xdr_encode_opaque_fixed(p, &fl->stateid.si_opaque,
				    sizeof(stateid_opaque_t));

	*p++ = cpu_to_be32(1);			/* single file handle */
	p = xdr_encode_opaque(p, fl->fh.data, fl->fh.size);

	p = xdr_encode_opaque(p, uid.buf, uid.len);
	p = xdr_encode_opaque(p, gid.buf, gid.len);

	*p++ = cpu_to_be32(fl->flags);
	*p++ = cpu_to_be32(0);			/* No stats collect hint */

	return 0;
}