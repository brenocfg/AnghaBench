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
struct dentry {int dummy; } ;
struct cachefiles_cache {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 struct dentry* cachefiles_check_active (struct cachefiles_cache*,struct dentry*,char*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 

int cachefiles_check_in_use(struct cachefiles_cache *cache, struct dentry *dir,
			    char *filename)
{
	struct dentry *victim;

	//_enter(",%pd/,%s",
	//       dir, filename);

	victim = cachefiles_check_active(cache, dir, filename);
	if (IS_ERR(victim))
		return PTR_ERR(victim);

	inode_unlock(d_inode(dir));
	dput(victim);
	//_leave(" = 0");
	return 0;
}