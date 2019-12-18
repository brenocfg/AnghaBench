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
 scalar_t__ PageUptodate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPageUptodate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_page_group_covers_page (struct nfs_page*) ; 

__attribute__((used)) static void nfs_mark_uptodate(struct nfs_page *req)
{
	if (PageUptodate(req->wb_page))
		return;
	if (!nfs_page_group_covers_page(req))
		return;
	SetPageUptodate(req->wb_page);
}