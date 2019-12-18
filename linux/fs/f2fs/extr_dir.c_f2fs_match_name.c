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
struct qstr {int /*<<< orphan*/  len; scalar_t__ name; } ;
struct inode {int dummy; } ;
struct fscrypt_str {int /*<<< orphan*/  len; scalar_t__ name; } ;
struct fscrypt_name {struct qstr* usr_fname; } ;
struct f2fs_sb_info {scalar_t__ s_encoding; } ;
struct f2fs_dir_entry {scalar_t__ hash_code; int /*<<< orphan*/  name_len; } ;
struct f2fs_dentry_ptr {scalar_t__* filename; struct inode* inode; } ;
typedef  scalar_t__ f2fs_hash_t ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_CASEFOLDED (struct inode*) ; 
 int /*<<< orphan*/  f2fs_ci_compare (struct inode*,struct qstr*,struct qstr*,int) ; 
 scalar_t__ fscrypt_match_name (struct fscrypt_name*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool f2fs_match_name(struct f2fs_dentry_ptr *d,
					struct f2fs_dir_entry *de,
					struct fscrypt_name *fname,
					struct fscrypt_str *cf_str,
					unsigned long bit_pos,
					f2fs_hash_t namehash)
{
#ifdef CONFIG_UNICODE
	struct inode *parent = d->inode;
	struct f2fs_sb_info *sbi = F2FS_I_SB(parent);
	struct qstr entry;
#endif

	if (de->hash_code != namehash)
		return false;

#ifdef CONFIG_UNICODE
	entry.name = d->filename[bit_pos];
	entry.len = de->name_len;

	if (sbi->s_encoding && IS_CASEFOLDED(parent)) {
		if (cf_str->name) {
			struct qstr cf = {.name = cf_str->name,
					  .len = cf_str->len};
			return !f2fs_ci_compare(parent, &cf, &entry, true);
		}
		return !f2fs_ci_compare(parent, fname->usr_fname, &entry,
					false);
	}
#endif
	if (fscrypt_match_name(fname, d->filename[bit_pos],
				le16_to_cpu(de->name_len)))
		return true;
	return false;
}