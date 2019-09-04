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
struct nfs4_xdr_opaque_data {struct nfs4_ff_layout_mirror* data; } ;
struct nfs4_ff_layout_mirror {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_put_mirror (struct nfs4_ff_layout_mirror*) ; 

__attribute__((used)) static void
ff_layout_free_layoutstats(struct nfs4_xdr_opaque_data *opaque)
{
	struct nfs4_ff_layout_mirror *mirror = opaque->data;

	ff_layout_put_mirror(mirror);
}