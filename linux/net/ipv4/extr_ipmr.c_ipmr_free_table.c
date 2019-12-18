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
struct mr_table {int /*<<< orphan*/  mfc_hash; int /*<<< orphan*/  ipmr_expire_timer; } ;

/* Variables and functions */
 int MRT_FLUSH_MFC ; 
 int MRT_FLUSH_MFC_STATIC ; 
 int MRT_FLUSH_VIFS ; 
 int MRT_FLUSH_VIFS_STATIC ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mr_table*) ; 
 int /*<<< orphan*/  mroute_clean_tables (struct mr_table*,int) ; 
 int /*<<< orphan*/  rhltable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmr_free_table(struct mr_table *mrt)
{
	del_timer_sync(&mrt->ipmr_expire_timer);
	mroute_clean_tables(mrt, MRT_FLUSH_VIFS | MRT_FLUSH_VIFS_STATIC |
				 MRT_FLUSH_MFC | MRT_FLUSH_MFC_STATIC);
	rhltable_destroy(&mrt->mfc_hash);
	kfree(mrt);
}