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
struct nfs_page {int dummy; } ;
struct nfs_open_context {int dummy; } ;
typedef  struct nfs_page nfs_lock_context ;

/* Variables and functions */
 struct nfs_page* ERR_CAST (struct nfs_page*) ; 
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 struct nfs_page* __nfs_create_request (struct nfs_page*,struct page*,unsigned int,unsigned int,unsigned int) ; 
 struct nfs_page* nfs_get_lock_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  nfs_page_group_init (struct nfs_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_put_lock_context (struct nfs_page*) ; 

struct nfs_page *
nfs_create_request(struct nfs_open_context *ctx, struct page *page,
		   unsigned int offset, unsigned int count)
{
	struct nfs_lock_context *l_ctx = nfs_get_lock_context(ctx);
	struct nfs_page *ret;

	if (IS_ERR(l_ctx))
		return ERR_CAST(l_ctx);
	ret = __nfs_create_request(l_ctx, page, offset, offset, count);
	if (!IS_ERR(ret))
		nfs_page_group_init(ret, NULL);
	nfs_put_lock_context(l_ctx);
	return ret;
}