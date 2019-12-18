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
struct path {struct dentry* dentry; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; } ;
struct dcookie_struct {struct path path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_COOKIE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcookie_cache ; 
 int /*<<< orphan*/  hash_dcookie (struct dcookie_struct*) ; 
 struct dcookie_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (struct path const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dcookie_struct *alloc_dcookie(const struct path *path)
{
	struct dcookie_struct *dcs = kmem_cache_alloc(dcookie_cache,
							GFP_KERNEL);
	struct dentry *d;
	if (!dcs)
		return NULL;

	d = path->dentry;
	spin_lock(&d->d_lock);
	d->d_flags |= DCACHE_COOKIE;
	spin_unlock(&d->d_lock);

	dcs->path = *path;
	path_get(path);
	hash_dcookie(dcs);
	return dcs;
}