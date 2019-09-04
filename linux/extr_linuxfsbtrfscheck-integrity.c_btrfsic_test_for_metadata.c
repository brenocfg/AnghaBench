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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct btrfsic_state {unsigned int metablock_size; int /*<<< orphan*/  csum_size; struct btrfs_fs_info* fs_info; } ;
struct btrfs_header {char* fsid; int /*<<< orphan*/  csum; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fsid; } ;

/* Variables and functions */
 int BTRFS_CSUM_SIZE ; 
 int /*<<< orphan*/  BTRFS_FSID_SIZE ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  btrfs_csum_final (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  crc32c (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfsic_test_for_metadata(struct btrfsic_state *state,
				     char **datav, unsigned int num_pages)
{
	struct btrfs_fs_info *fs_info = state->fs_info;
	struct btrfs_header *h;
	u8 csum[BTRFS_CSUM_SIZE];
	u32 crc = ~(u32)0;
	unsigned int i;

	if (num_pages * PAGE_SIZE < state->metablock_size)
		return 1; /* not metadata */
	num_pages = state->metablock_size >> PAGE_SHIFT;
	h = (struct btrfs_header *)datav[0];

	if (memcmp(h->fsid, fs_info->fsid, BTRFS_FSID_SIZE))
		return 1;

	for (i = 0; i < num_pages; i++) {
		u8 *data = i ? datav[i] : (datav[i] + BTRFS_CSUM_SIZE);
		size_t sublen = i ? PAGE_SIZE :
				    (PAGE_SIZE - BTRFS_CSUM_SIZE);

		crc = crc32c(crc, data, sublen);
	}
	btrfs_csum_final(crc, csum);
	if (memcmp(csum, h->csum, state->csum_size))
		return 1;

	return 0; /* is metadata */
}