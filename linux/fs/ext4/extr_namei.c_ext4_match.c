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
struct qstr {int /*<<< orphan*/  len; scalar_t__ name; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fscrypt_name {int /*<<< orphan*/  crypto_buf; int /*<<< orphan*/  disk_name; struct qstr* usr_fname; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; scalar_t__ name; } ;
struct ext4_filename {struct qstr* usr_fname; TYPE_1__ cf_name; int /*<<< orphan*/  crypto_buf; int /*<<< orphan*/  disk_name; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  name_len; scalar_t__ name; int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {scalar_t__ s_encoding; } ;

/* Variables and functions */
 TYPE_2__* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CASEFOLDED (struct inode const*) ; 
 int /*<<< orphan*/  ext4_ci_compare (struct inode const*,struct qstr*,struct qstr const*,int) ; 
 int fscrypt_match_name (struct fscrypt_name*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ext4_match(const struct inode *parent,
			      const struct ext4_filename *fname,
			      const struct ext4_dir_entry_2 *de)
{
	struct fscrypt_name f;
#ifdef CONFIG_UNICODE
	const struct qstr entry = {.name = de->name, .len = de->name_len};
#endif

	if (!de->inode)
		return false;

	f.usr_fname = fname->usr_fname;
	f.disk_name = fname->disk_name;
#ifdef CONFIG_FS_ENCRYPTION
	f.crypto_buf = fname->crypto_buf;
#endif

#ifdef CONFIG_UNICODE
	if (EXT4_SB(parent->i_sb)->s_encoding && IS_CASEFOLDED(parent)) {
		if (fname->cf_name.name) {
			struct qstr cf = {.name = fname->cf_name.name,
					  .len = fname->cf_name.len};
			return !ext4_ci_compare(parent, &cf, &entry, true);
		}
		return !ext4_ci_compare(parent, fname->usr_fname, &entry,
					false);
	}
#endif

	return fscrypt_match_name(&f, de->name, de->name_len);
}