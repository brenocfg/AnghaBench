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
struct inode {int dummy; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  rec_len; scalar_t__ name_len; int /*<<< orphan*/  name; scalar_t__ inode; } ;
struct dx_map_entry {int offs; int /*<<< orphan*/  size; int /*<<< orphan*/  hash; } ;
struct dx_hash_info {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 struct ext4_dir_entry_2* ext4_next_entry (struct ext4_dir_entry_2*,unsigned int) ; 
 int /*<<< orphan*/  ext4fs_dirhash (struct inode*,int /*<<< orphan*/ ,scalar_t__,struct dx_hash_info*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dx_make_map(struct inode *dir, struct ext4_dir_entry_2 *de,
		       unsigned blocksize, struct dx_hash_info *hinfo,
		       struct dx_map_entry *map_tail)
{
	int count = 0;
	char *base = (char *) de;
	struct dx_hash_info h = *hinfo;

	while ((char *) de < base + blocksize) {
		if (de->name_len && de->inode) {
			ext4fs_dirhash(dir, de->name, de->name_len, &h);
			map_tail--;
			map_tail->hash = h.hash;
			map_tail->offs = ((char *) de - base)>>2;
			map_tail->size = le16_to_cpu(de->rec_len);
			count++;
			cond_resched();
		}
		/* XXX: do we need to check rec_len == 0 case? -Chris */
		de = ext4_next_entry(de, blocksize);
	}
	return count;
}