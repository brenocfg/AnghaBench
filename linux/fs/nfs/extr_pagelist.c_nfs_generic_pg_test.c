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
struct page {int dummy; } ;
struct nfs_pgio_mirror {int pg_count; int pg_bsize; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct nfs_page {int wb_bytes; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 size_t min (int,size_t) ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 

size_t nfs_generic_pg_test(struct nfs_pageio_descriptor *desc,
			   struct nfs_page *prev, struct nfs_page *req)
{
	struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);


	if (mirror->pg_count > mirror->pg_bsize) {
		/* should never happen */
		WARN_ON_ONCE(1);
		return 0;
	}

	/*
	 * Limit the request size so that we can still allocate a page array
	 * for it without upsetting the slab allocator.
	 */
	if (((mirror->pg_count + req->wb_bytes) >> PAGE_SHIFT) *
			sizeof(struct page *) > PAGE_SIZE)
		return 0;

	return min(mirror->pg_bsize - mirror->pg_count, (size_t)req->wb_bytes);
}