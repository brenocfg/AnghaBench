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
struct inode {int i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct fscrypt_mode {int dummy; } ;
struct fscrypt_info {size_t ci_data_mode; size_t ci_filename_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct fscrypt_mode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFMT ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int) ; 
 struct fscrypt_mode* available_modes ; 
 int /*<<< orphan*/  fscrypt_valid_enc_modes (size_t,size_t) ; 
 int /*<<< orphan*/  fscrypt_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static struct fscrypt_mode *
select_encryption_mode(const struct fscrypt_info *ci, const struct inode *inode)
{
	if (!fscrypt_valid_enc_modes(ci->ci_data_mode, ci->ci_filename_mode)) {
		fscrypt_warn(inode->i_sb,
			     "inode %lu uses unsupported encryption modes (contents mode %d, filenames mode %d)",
			     inode->i_ino, ci->ci_data_mode,
			     ci->ci_filename_mode);
		return ERR_PTR(-EINVAL);
	}

	if (S_ISREG(inode->i_mode))
		return &available_modes[ci->ci_data_mode];

	if (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode))
		return &available_modes[ci->ci_filename_mode];

	WARN_ONCE(1, "fscrypt: filesystem tried to load encryption info for inode %lu, which is not encryptable (file type %d)\n",
		  inode->i_ino, (inode->i_mode & S_IFMT));
	return ERR_PTR(-EINVAL);
}