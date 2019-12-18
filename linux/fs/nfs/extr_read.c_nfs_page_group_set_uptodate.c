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
struct nfs_page {int /*<<< orphan*/  wb_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_UPTODATE ; 
 int /*<<< orphan*/  SetPageUptodate (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_page_group_sync_on_bit (struct nfs_page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_page_group_set_uptodate(struct nfs_page *req)
{
	if (nfs_page_group_sync_on_bit(req, PG_UPTODATE))
		SetPageUptodate(req->wb_page);
}