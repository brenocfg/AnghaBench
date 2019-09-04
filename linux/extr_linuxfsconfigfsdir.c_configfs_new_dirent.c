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
struct configfs_dirent {int s_type; int /*<<< orphan*/  s_children; int /*<<< orphan*/  s_sibling; void* s_element; int /*<<< orphan*/  s_links; int /*<<< orphan*/  s_count; } ;

/* Variables and functions */
 int CONFIGFS_USET_DROPPING ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct configfs_dirent* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  configfs_dir_cachep ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_init_dirent_depth (struct configfs_dirent*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct configfs_dirent*) ; 
 struct configfs_dirent* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct configfs_dirent *configfs_new_dirent(struct configfs_dirent *parent_sd,
						   void *element, int type)
{
	struct configfs_dirent * sd;

	sd = kmem_cache_zalloc(configfs_dir_cachep, GFP_KERNEL);
	if (!sd)
		return ERR_PTR(-ENOMEM);

	atomic_set(&sd->s_count, 1);
	INIT_LIST_HEAD(&sd->s_links);
	INIT_LIST_HEAD(&sd->s_children);
	sd->s_element = element;
	sd->s_type = type;
	configfs_init_dirent_depth(sd);
	spin_lock(&configfs_dirent_lock);
	if (parent_sd->s_type & CONFIGFS_USET_DROPPING) {
		spin_unlock(&configfs_dirent_lock);
		kmem_cache_free(configfs_dir_cachep, sd);
		return ERR_PTR(-ENOENT);
	}
	list_add(&sd->s_sibling, &parent_sd->s_children);
	spin_unlock(&configfs_dirent_lock);

	return sd;
}