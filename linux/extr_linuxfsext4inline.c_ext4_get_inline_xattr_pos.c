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
struct inode {int dummy; } ;
struct ext4_xattr_ibody_header {int dummy; } ;
struct ext4_xattr_entry {int /*<<< orphan*/  e_value_offs; } ;
struct ext4_iloc {int dummy; } ;
struct TYPE_2__ {int i_inline_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ IFIRST (struct ext4_xattr_ibody_header*) ; 
 struct ext4_xattr_ibody_header* IHDR (struct inode*,scalar_t__) ; 
 scalar_t__ ext4_raw_inode (struct ext4_iloc*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *ext4_get_inline_xattr_pos(struct inode *inode,
				       struct ext4_iloc *iloc)
{
	struct ext4_xattr_entry *entry;
	struct ext4_xattr_ibody_header *header;

	BUG_ON(!EXT4_I(inode)->i_inline_off);

	header = IHDR(inode, ext4_raw_inode(iloc));
	entry = (struct ext4_xattr_entry *)((void *)ext4_raw_inode(iloc) +
					    EXT4_I(inode)->i_inline_off);

	return (void *)IFIRST(header) + le16_to_cpu(entry->e_value_offs);
}