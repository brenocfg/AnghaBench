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
struct nfs_pageio_descriptor {int dummy; } ;
struct nfs_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  is_aligned_req (struct nfs_pageio_descriptor*,struct nfs_page*,int /*<<< orphan*/ ,int) ; 
 size_t pnfs_generic_pg_test (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ; 

__attribute__((used)) static size_t
bl_pg_test_write(struct nfs_pageio_descriptor *pgio, struct nfs_page *prev,
		 struct nfs_page *req)
{
	if (!is_aligned_req(pgio, req, PAGE_SIZE, true))
		return 0;
	return pnfs_generic_pg_test(pgio, prev, req);
}