#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct unicode_map {int dummy; } ;
struct f2fs_sb_info {TYPE_1__* sb; int /*<<< orphan*/  s_encoding_flags; struct unicode_map* s_encoding; int /*<<< orphan*/  raw_super; } ;
struct f2fs_sb_encodings {scalar_t__ version; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * s_d_op; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct unicode_map*) ; 
 int PTR_ERR (struct unicode_map*) ; 
 int /*<<< orphan*/  f2fs_dentry_ops ; 
 int /*<<< orphan*/  f2fs_err (struct f2fs_sb_info*,char*,...) ; 
 int /*<<< orphan*/  f2fs_info (struct f2fs_sb_info*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_sb_has_casefold (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_has_encrypt (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_sb_read_encoding (int /*<<< orphan*/ ,struct f2fs_sb_encodings const**,int /*<<< orphan*/ *) ; 
 struct unicode_map* utf8_load (scalar_t__) ; 

__attribute__((used)) static int f2fs_setup_casefold(struct f2fs_sb_info *sbi)
{
#ifdef CONFIG_UNICODE
	if (f2fs_sb_has_casefold(sbi) && !sbi->s_encoding) {
		const struct f2fs_sb_encodings *encoding_info;
		struct unicode_map *encoding;
		__u16 encoding_flags;

		if (f2fs_sb_has_encrypt(sbi)) {
			f2fs_err(sbi,
				"Can't mount with encoding and encryption");
			return -EINVAL;
		}

		if (f2fs_sb_read_encoding(sbi->raw_super, &encoding_info,
					  &encoding_flags)) {
			f2fs_err(sbi,
				 "Encoding requested by superblock is unknown");
			return -EINVAL;
		}

		encoding = utf8_load(encoding_info->version);
		if (IS_ERR(encoding)) {
			f2fs_err(sbi,
				 "can't mount with superblock charset: %s-%s "
				 "not supported by the kernel. flags: 0x%x.",
				 encoding_info->name, encoding_info->version,
				 encoding_flags);
			return PTR_ERR(encoding);
		}
		f2fs_info(sbi, "Using encoding defined by superblock: "
			 "%s-%s with flags 0x%hx", encoding_info->name,
			 encoding_info->version?:"\b", encoding_flags);

		sbi->s_encoding = encoding;
		sbi->s_encoding_flags = encoding_flags;
		sbi->sb->s_d_op = &f2fs_dentry_ops;
	}
#else
	if (f2fs_sb_has_casefold(sbi)) {
		f2fs_err(sbi, "Filesystem with casefold feature cannot be mounted without CONFIG_UNICODE");
		return -EINVAL;
	}
#endif
	return 0;
}