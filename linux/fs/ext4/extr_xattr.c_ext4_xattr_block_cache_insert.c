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
struct mb_cache {int dummy; } ;
struct ext4_xattr_header {int /*<<< orphan*/  h_refcount; int /*<<< orphan*/  h_hash; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 struct ext4_xattr_header* BHDR (struct buffer_head*) ; 
 int EBUSY ; 
 scalar_t__ EXT4_XATTR_REFCOUNT_MAX ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,...) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mb_cache_entry_create (struct mb_cache*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ext4_xattr_block_cache_insert(struct mb_cache *ea_block_cache,
			      struct buffer_head *bh)
{
	struct ext4_xattr_header *header = BHDR(bh);
	__u32 hash = le32_to_cpu(header->h_hash);
	int reusable = le32_to_cpu(header->h_refcount) <
		       EXT4_XATTR_REFCOUNT_MAX;
	int error;

	if (!ea_block_cache)
		return;
	error = mb_cache_entry_create(ea_block_cache, GFP_NOFS, hash,
				      bh->b_blocknr, reusable);
	if (error) {
		if (error == -EBUSY)
			ea_bdebug(bh, "already in cache");
	} else
		ea_bdebug(bh, "inserting [%x]", (int)hash);
}