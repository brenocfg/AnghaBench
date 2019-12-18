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
typedef  int /*<<< orphan*/  u16 ;
struct crypto_shash {int dummy; } ;
struct btrfs_fs_info {struct crypto_shash* csum_shash; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,char const*) ; 
 char* btrfs_super_csum_name (int /*<<< orphan*/ ) ; 
 struct crypto_shash* crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_init_csum_hash(struct btrfs_fs_info *fs_info, u16 csum_type)
{
	struct crypto_shash *csum_shash;
	const char *csum_name = btrfs_super_csum_name(csum_type);

	csum_shash = crypto_alloc_shash(csum_name, 0, 0);

	if (IS_ERR(csum_shash)) {
		btrfs_err(fs_info, "error allocating %s hash for checksum",
			  csum_name);
		return PTR_ERR(csum_shash);
	}

	fs_info->csum_shash = csum_shash;

	return 0;
}