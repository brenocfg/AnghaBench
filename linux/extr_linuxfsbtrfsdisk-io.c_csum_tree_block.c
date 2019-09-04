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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct extent_buffer {unsigned long len; int /*<<< orphan*/  start; } ;
struct btrfs_fs_info {TYPE_1__* sb; int /*<<< orphan*/  super_copy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int BTRFS_CSUM_SIZE ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  btrfs_csum_data (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  btrfs_csum_final (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btrfs_header_level (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_super_csum_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_warn_rl (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int map_private_extent_buffer (struct extent_buffer*,unsigned long,int,char**,unsigned long*,unsigned long*) ; 
 scalar_t__ memcmp_extent_buffer (struct extent_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_extent_buffer (struct extent_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csum_tree_block(struct btrfs_fs_info *fs_info,
			   struct extent_buffer *buf,
			   int verify)
{
	u16 csum_size = btrfs_super_csum_size(fs_info->super_copy);
	char result[BTRFS_CSUM_SIZE];
	unsigned long len;
	unsigned long cur_len;
	unsigned long offset = BTRFS_CSUM_SIZE;
	char *kaddr;
	unsigned long map_start;
	unsigned long map_len;
	int err;
	u32 crc = ~(u32)0;

	len = buf->len - offset;
	while (len > 0) {
		err = map_private_extent_buffer(buf, offset, 32,
					&kaddr, &map_start, &map_len);
		if (err)
			return err;
		cur_len = min(len, map_len - (offset - map_start));
		crc = btrfs_csum_data(kaddr + offset - map_start,
				      crc, cur_len);
		len -= cur_len;
		offset += cur_len;
	}
	memset(result, 0, BTRFS_CSUM_SIZE);

	btrfs_csum_final(crc, result);

	if (verify) {
		if (memcmp_extent_buffer(buf, result, 0, csum_size)) {
			u32 val;
			u32 found = 0;
			memcpy(&found, result, csum_size);

			read_extent_buffer(buf, &val, 0, csum_size);
			btrfs_warn_rl(fs_info,
				"%s checksum verify failed on %llu wanted %X found %X level %d",
				fs_info->sb->s_id, buf->start,
				val, found, btrfs_header_level(buf));
			return -EUCLEAN;
		}
	} else {
		write_extent_buffer(buf, result, 0, csum_size);
	}

	return 0;
}