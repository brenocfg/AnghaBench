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
struct inode {TYPE_1__* i_sb; } ;
struct fiemap_extent_info {int dummy; } ;
struct extent_status {scalar_t__ es_len; scalar_t__ es_pblk; scalar_t__ es_lblk; } ;
typedef  scalar_t__ ext4_lblk_t ;
typedef  unsigned char __u64 ;
struct TYPE_2__ {unsigned char s_blocksize_bits; } ;

/* Variables and functions */
 unsigned int EXT4_FIEMAP_EXTENT_HOLE ; 
 unsigned int FIEMAP_EXTENT_DELALLOC ; 
 unsigned int FIEMAP_EXTENT_LAST ; 
 unsigned int FIEMAP_EXTENT_UNKNOWN ; 
 unsigned int FIEMAP_EXTENT_UNWRITTEN ; 
 scalar_t__ ext4_es_is_delayed (struct extent_status*) ; 
 scalar_t__ ext4_es_is_hole (struct extent_status*) ; 
 scalar_t__ ext4_es_is_unwritten (struct extent_status*) ; 
 int /*<<< orphan*/  ext4_es_lookup_extent (struct inode*,scalar_t__,scalar_t__*,struct extent_status*) ; 
 scalar_t__ ext4_es_pblock (struct extent_status*) ; 
 int fiemap_fill_next_extent (struct fiemap_extent_info*,unsigned char,unsigned char,unsigned char,unsigned int) ; 

__attribute__((used)) static int ext4_fill_es_cache_info(struct inode *inode,
				   ext4_lblk_t block, ext4_lblk_t num,
				   struct fiemap_extent_info *fieinfo)
{
	ext4_lblk_t next, end = block + num - 1;
	struct extent_status es;
	unsigned char blksize_bits = inode->i_sb->s_blocksize_bits;
	unsigned int flags;
	int err;

	while (block <= end) {
		next = 0;
		flags = 0;
		if (!ext4_es_lookup_extent(inode, block, &next, &es))
			break;
		if (ext4_es_is_unwritten(&es))
			flags |= FIEMAP_EXTENT_UNWRITTEN;
		if (ext4_es_is_delayed(&es))
			flags |= (FIEMAP_EXTENT_DELALLOC |
				  FIEMAP_EXTENT_UNKNOWN);
		if (ext4_es_is_hole(&es))
			flags |= EXT4_FIEMAP_EXTENT_HOLE;
		if (next == 0)
			flags |= FIEMAP_EXTENT_LAST;
		if (flags & (FIEMAP_EXTENT_DELALLOC|
			     EXT4_FIEMAP_EXTENT_HOLE))
			es.es_pblk = 0;
		else
			es.es_pblk = ext4_es_pblock(&es);
		err = fiemap_fill_next_extent(fieinfo,
				(__u64)es.es_lblk << blksize_bits,
				(__u64)es.es_pblk << blksize_bits,
				(__u64)es.es_len << blksize_bits,
				flags);
		if (next == 0)
			break;
		block = next;
		if (err < 0)
			return err;
		if (err == 1)
			return 0;
	}
	return 0;
}