#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_3__ {char* name; size_t len; } ;
struct inode {TYPE_1__ d_name; struct super_block* i_sb; } ;
struct dentry {TYPE_1__ d_name; struct super_block* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct CodaFid {TYPE_2__ member_0; } ;

/* Variables and functions */
 size_t CODA_MAXNAMLEN ; 
 int CODA_NOCACHE ; 
 int C_PURGE ; 
 int C_VATTR ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 struct inode* coda_cnode_make (struct CodaFid*,struct super_block*) ; 
 struct inode* coda_cnode_makectl (struct super_block*) ; 
 int /*<<< orphan*/  coda_flag_inode (struct inode*,int) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 int /*<<< orphan*/  coda_i2s (struct inode*) ; 
 scalar_t__ coda_iscontrol (char const*,size_t) ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 scalar_t__ is_root_inode (struct inode*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,size_t) ; 
 int venus_lookup (struct super_block*,int /*<<< orphan*/ ,char const*,size_t,int*,struct CodaFid*) ; 

__attribute__((used)) static struct dentry *coda_lookup(struct inode *dir, struct dentry *entry, unsigned int flags)
{
	struct super_block *sb = dir->i_sb;
	const char *name = entry->d_name.name;
	size_t length = entry->d_name.len;
	struct inode *inode;
	int type = 0;

	if (length > CODA_MAXNAMLEN) {
		pr_err("name too long: lookup, %s %zu\n",
		       coda_i2s(dir), length);
		return ERR_PTR(-ENAMETOOLONG);
	}

	/* control object, create inode on the fly */
	if (is_root_inode(dir) && coda_iscontrol(name, length)) {
		inode = coda_cnode_makectl(sb);
		type = CODA_NOCACHE;
	} else {
		struct CodaFid fid = { { 0, } };
		int error = venus_lookup(sb, coda_i2f(dir), name, length,
				     &type, &fid);
		inode = !error ? coda_cnode_make(&fid, sb) : ERR_PTR(error);
	}

	if (!IS_ERR(inode) && (type & CODA_NOCACHE))
		coda_flag_inode(inode, C_VATTR | C_PURGE);

	if (inode == ERR_PTR(-ENOENT))
		inode = NULL;

	return d_splice_alias(inode, entry);
}