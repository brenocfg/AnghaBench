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
typedef  int /*<<< orphan*/  umode_t ;
struct dentry {int dummy; } ;
struct cache_detail {struct dentry* pipefs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 struct dentry* rpc_create_cache_dir (struct dentry*,char const*,int /*<<< orphan*/ ,struct cache_detail*) ; 

int sunrpc_cache_register_pipefs(struct dentry *parent,
				 const char *name, umode_t umode,
				 struct cache_detail *cd)
{
	struct dentry *dir = rpc_create_cache_dir(parent, name, umode, cd);
	if (IS_ERR(dir))
		return PTR_ERR(dir);
	cd->pipefs = dir;
	return 0;
}