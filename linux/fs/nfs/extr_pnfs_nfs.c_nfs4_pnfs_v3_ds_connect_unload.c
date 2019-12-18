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

/* Variables and functions */
 int /*<<< orphan*/ * get_v3_ds_connect ; 
 int /*<<< orphan*/  nfs3_set_ds_client ; 
 int /*<<< orphan*/  symbol_put (int /*<<< orphan*/ ) ; 

void nfs4_pnfs_v3_ds_connect_unload(void)
{
	if (get_v3_ds_connect) {
		symbol_put(nfs3_set_ds_client);
		get_v3_ds_connect = NULL;
	}
}