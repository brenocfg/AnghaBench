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
struct nfs_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_page_group_lock (struct nfs_page*) ; 
 int nfs_page_group_sync_on_bit_locked (struct nfs_page*,unsigned int) ; 
 int /*<<< orphan*/  nfs_page_group_unlock (struct nfs_page*) ; 

bool nfs_page_group_sync_on_bit(struct nfs_page *req, unsigned int bit)
{
	bool ret;

	nfs_page_group_lock(req);
	ret = nfs_page_group_sync_on_bit_locked(req, bit);
	nfs_page_group_unlock(req);

	return ret;
}