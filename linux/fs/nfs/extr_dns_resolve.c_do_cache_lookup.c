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
struct nfs_dns_ent {int /*<<< orphan*/  h; } ;
struct nfs_cache_defer_req {int /*<<< orphan*/  req; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int cache_check (struct cache_detail*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs_dns_ent* nfs_dns_lookup (struct cache_detail*,struct nfs_dns_ent*) ; 

__attribute__((used)) static int do_cache_lookup(struct cache_detail *cd,
		struct nfs_dns_ent *key,
		struct nfs_dns_ent **item,
		struct nfs_cache_defer_req *dreq)
{
	int ret = -ENOMEM;

	*item = nfs_dns_lookup(cd, key);
	if (*item) {
		ret = cache_check(cd, &(*item)->h, &dreq->req);
		if (ret)
			*item = NULL;
	}
	return ret;
}