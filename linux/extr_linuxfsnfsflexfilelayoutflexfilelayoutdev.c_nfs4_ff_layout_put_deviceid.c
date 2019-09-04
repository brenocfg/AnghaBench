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
struct nfs4_ff_layout_ds {int /*<<< orphan*/  id_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct nfs4_ff_layout_ds*) ; 
 int /*<<< orphan*/  nfs4_put_deviceid_node (int /*<<< orphan*/ *) ; 

void nfs4_ff_layout_put_deviceid(struct nfs4_ff_layout_ds *mirror_ds)
{
	if (!IS_ERR_OR_NULL(mirror_ds))
		nfs4_put_deviceid_node(&mirror_ds->id_node);
}