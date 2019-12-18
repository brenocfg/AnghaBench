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
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;
struct cache_detail {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* rpc_d_lookup_sb (struct super_block*,char*) ; 
 int sunrpc_cache_register_pipefs (struct dentry*,int /*<<< orphan*/ ,int,struct cache_detail*) ; 

int nfs_cache_register_sb(struct super_block *sb, struct cache_detail *cd)
{
	int ret;
	struct dentry *dir;

	dir = rpc_d_lookup_sb(sb, "cache");
	ret = sunrpc_cache_register_pipefs(dir, cd->name, 0600, cd);
	dput(dir);
	return ret;
}