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
struct nfs4_layoutreturn_args {TYPE_1__* layout; } ;
struct nfs4_flexfile_layoutreturn_args {int num_dev; int /*<<< orphan*/ * devinfo; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  plh_stateid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  ff_layout_encode_ff_iostat (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void ff_layout_encode_iostats_array(struct xdr_stream *xdr,
		const struct nfs4_layoutreturn_args *args,
		struct nfs4_flexfile_layoutreturn_args *ff_args)
{
	__be32 *p;
	int i;

	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(ff_args->num_dev);
	for (i = 0; i < ff_args->num_dev; i++)
		ff_layout_encode_ff_iostat(xdr,
				&args->layout->plh_stateid,
				&ff_args->devinfo[i]);
}