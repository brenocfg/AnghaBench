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
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfs42_layoutstat_devinfo {TYPE_1__ ld_private; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_encode_ff_iostat_head (struct xdr_stream*,int /*<<< orphan*/  const*,struct nfs42_layoutstat_devinfo const*) ; 
 int /*<<< orphan*/  ff_layout_encode_ff_layoutupdate (struct xdr_stream*,struct nfs42_layoutstat_devinfo const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ff_layout_encode_ff_iostat(struct xdr_stream *xdr,
			    const nfs4_stateid *stateid,
			    const struct nfs42_layoutstat_devinfo *devinfo)
{
	ff_layout_encode_ff_iostat_head(xdr, stateid, devinfo);
	ff_layout_encode_ff_layoutupdate(xdr, devinfo,
			devinfo->ld_private.data);
}