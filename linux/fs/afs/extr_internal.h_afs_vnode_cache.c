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
struct fscache_cookie {int dummy; } ;
struct afs_vnode {struct fscache_cookie* cache; } ;

/* Variables and functions */

__attribute__((used)) static inline struct fscache_cookie *afs_vnode_cache(struct afs_vnode *vnode)
{
#ifdef CONFIG_AFS_FSCACHE
	return vnode->cache;
#else
	return NULL;
#endif
}