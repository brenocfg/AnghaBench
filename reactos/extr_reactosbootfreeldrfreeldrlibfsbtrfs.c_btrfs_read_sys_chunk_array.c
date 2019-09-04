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
typedef  scalar_t__ u16 ;
struct btrfs_super_block {scalar_t__ sys_chunk_array_size; scalar_t__ sys_chunk_array; } ;
struct btrfs_disk_key {int /*<<< orphan*/  type; int /*<<< orphan*/  offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_chunk {scalar_t__ length; scalar_t__ owner; scalar_t__ stripe_len; scalar_t__ type; scalar_t__ io_align; scalar_t__ io_width; scalar_t__ sector_size; scalar_t__ num_stripes; scalar_t__ sub_stripes; } ;
struct TYPE_2__ {struct btrfs_super_block SuperBlock; } ;

/* Variables and functions */
 TYPE_1__* BtrFsInfo ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ btrfs_chunk_item_size (scalar_t__) ; 
 int /*<<< orphan*/  insert_map (struct btrfs_disk_key const*,struct btrfs_chunk*) ; 

__attribute__((used)) static void btrfs_read_sys_chunk_array()
{
    struct btrfs_super_block *sb = &BtrFsInfo->SuperBlock;
    struct btrfs_disk_key *key;
    struct btrfs_chunk *chunk;
    u16 cur;

    /* read chunk array in superblock */
    TRACE("reading chunk array\n-----------------------------\n");
    cur = 0;
    while (cur < sb->sys_chunk_array_size)
    {
        key = (struct btrfs_disk_key *) (sb->sys_chunk_array + cur);
        TRACE("chunk key objectid: %llx, offset: %llx, type: %u\n", key->objectid, key->offset, key->type);
        cur += sizeof(*key);
        chunk = (struct btrfs_chunk *) (sb->sys_chunk_array + cur);
        TRACE("chunk length: %llx\n", chunk->length);
        TRACE("chunk owner: %llu\n", chunk->owner);
        TRACE("chunk stripe_len: %llx\n", chunk->stripe_len);
        TRACE("chunk type: %llu\n", chunk->type);
        TRACE("chunk io_align: %u\n", chunk->io_align);
        TRACE("chunk io_width: %u\n", chunk->io_width);
        TRACE("chunk sector_size: %u\n", chunk->sector_size);
        TRACE("chunk num_stripes: %u\n", chunk->num_stripes);
        TRACE("chunk sub_stripes: %u\n", chunk->sub_stripes);

        cur += btrfs_chunk_item_size(chunk->num_stripes);
        TRACE("read_sys_chunk_array() cur=%d\n", cur);
        insert_map((const struct btrfs_disk_key *) key, chunk);
    }
}