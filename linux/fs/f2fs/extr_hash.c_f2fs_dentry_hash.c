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
struct unicode_map {int dummy; } ;
typedef  struct qstr {int len; unsigned char* name; } const qstr ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fscrypt_name {int dummy; } ;
struct f2fs_sb_info {struct unicode_map* s_encoding; } ;
typedef  int f2fs_hash_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct f2fs_sb_info* F2FS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_CASEFOLDED (struct inode const*) ; 
 int PATH_MAX ; 
 int __f2fs_dentry_hash (struct qstr const*,struct fscrypt_name*) ; 
 unsigned char* f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (unsigned char*) ; 
 int utf8_casefold (struct unicode_map const*,struct qstr const*,unsigned char*,int) ; 

f2fs_hash_t f2fs_dentry_hash(const struct inode *dir,
		const struct qstr *name_info, struct fscrypt_name *fname)
{
#ifdef CONFIG_UNICODE
	struct f2fs_sb_info *sbi = F2FS_SB(dir->i_sb);
	const struct unicode_map *um = sbi->s_encoding;
	int r, dlen;
	unsigned char *buff;
	struct qstr folded;

	if (!name_info->len || !IS_CASEFOLDED(dir))
		goto opaque_seq;

	buff = f2fs_kzalloc(sbi, sizeof(char) * PATH_MAX, GFP_KERNEL);
	if (!buff)
		return -ENOMEM;

	dlen = utf8_casefold(um, name_info, buff, PATH_MAX);
	if (dlen < 0) {
		kvfree(buff);
		goto opaque_seq;
	}
	folded.name = buff;
	folded.len = dlen;
	r = __f2fs_dentry_hash(&folded, fname);

	kvfree(buff);
	return r;

opaque_seq:
#endif
	return __f2fs_dentry_hash(name_info, fname);
}