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
struct configfs_dirent {int s_type; int /*<<< orphan*/  s_frag; int /*<<< orphan*/  s_iattr; } ;

/* Variables and functions */
 int CONFIGFS_ROOT ; 
 int /*<<< orphan*/  configfs_dir_cachep ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct configfs_dirent*) ; 
 int /*<<< orphan*/  put_fragment (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void release_configfs_dirent(struct configfs_dirent * sd)
{
	if (!(sd->s_type & CONFIGFS_ROOT)) {
		kfree(sd->s_iattr);
		put_fragment(sd->s_frag);
		kmem_cache_free(configfs_dir_cachep, sd);
	}
}