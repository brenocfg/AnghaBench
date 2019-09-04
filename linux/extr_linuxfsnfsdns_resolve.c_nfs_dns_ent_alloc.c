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
struct cache_head {int dummy; } ;
struct nfs_dns_ent {struct cache_head h; scalar_t__ addrlen; scalar_t__ namelen; int /*<<< orphan*/ * hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs_dns_ent* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cache_head *nfs_dns_ent_alloc(void)
{
	struct nfs_dns_ent *item = kmalloc(sizeof(*item), GFP_KERNEL);

	if (item != NULL) {
		item->hostname = NULL;
		item->namelen = 0;
		item->addrlen = 0;
		return &item->h;
	}
	return NULL;
}