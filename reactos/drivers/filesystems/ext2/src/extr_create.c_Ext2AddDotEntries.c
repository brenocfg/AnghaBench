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
struct inode {int i_nlink; TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct ext3_dir_entry_2 {int name_len; int /*<<< orphan*/  name; void* rec_len; void* inode; } ;
struct ext2_icb {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  ext3_lblk_t ;
struct TYPE_2__ {scalar_t__ s_blocksize; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ EXT3_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  Ext2WinntError (int) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct buffer_head* ext3_append (struct ext2_icb*,struct inode*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ext3_mark_inode_dirty (struct ext2_icb*,struct inode*) ; 
 int /*<<< orphan*/  ext3_set_de_type (TYPE_1__*,struct ext3_dir_entry_2*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

NTSTATUS Ext2AddDotEntries(struct ext2_icb *icb, struct inode *dir,
                           struct inode *inode)
{
    struct ext3_dir_entry_2 * de;
    struct buffer_head * bh;
    ext3_lblk_t block = 0;
    int rc = 0;

    bh = ext3_append(icb, inode, &block, &rc);
    if (!bh) {
        goto errorout;
    }

    de = (struct ext3_dir_entry_2 *) bh->b_data;
    de->inode = cpu_to_le32(inode->i_ino);
    de->name_len = 1;
    de->rec_len = cpu_to_le16(EXT3_DIR_REC_LEN(de->name_len));
    strcpy (de->name, ".");
    ext3_set_de_type(inode->i_sb, de, S_IFDIR);
    de = (struct ext3_dir_entry_2 *)
         ((char *) de + le16_to_cpu(de->rec_len));
    de->inode = cpu_to_le32(dir->i_ino);
    de->rec_len = cpu_to_le16(inode->i_sb->s_blocksize-EXT3_DIR_REC_LEN(1));
    de->name_len = 2;
    strcpy (de->name, "..");
    ext3_set_de_type(inode->i_sb, de, S_IFDIR);
    inode->i_nlink = 2;
    set_buffer_dirty(bh);
    ext3_mark_inode_dirty(icb, inode);

errorout:
    if (bh)
        __brelse (bh);

    return Ext2WinntError(rc);
}