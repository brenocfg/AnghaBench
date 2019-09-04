#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_7__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_6__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_5__ {void* tv_nsec; void* tv_sec; } ;
struct inode {int /*<<< orphan*/  i_sb; TYPE_3__ i_mtime; TYPE_2__ i_ctime; TYPE_1__ i_atime; int /*<<< orphan*/  i_mode; } ;
struct f2fs_inode {char* i_name; int /*<<< orphan*/  i_inline; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_advise; int /*<<< orphan*/  i_mtime_nsec; int /*<<< orphan*/  i_ctime_nsec; int /*<<< orphan*/  i_atime_nsec; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mode; } ;
struct TYPE_8__ {void* i_flags; int /*<<< orphan*/  i_advise; } ;

/* Variables and functions */
 TYPE_4__* F2FS_I (struct inode*) ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,void*) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_enc_name (struct inode*) ; 
 int /*<<< orphan*/  ino_of_node (struct page*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recover_inline_flags (struct inode*,struct f2fs_inode*) ; 

__attribute__((used)) static void recover_inode(struct inode *inode, struct page *page)
{
	struct f2fs_inode *raw = F2FS_INODE(page);
	char *name;

	inode->i_mode = le16_to_cpu(raw->i_mode);
	f2fs_i_size_write(inode, le64_to_cpu(raw->i_size));
	inode->i_atime.tv_sec = le64_to_cpu(raw->i_atime);
	inode->i_ctime.tv_sec = le64_to_cpu(raw->i_ctime);
	inode->i_mtime.tv_sec = le64_to_cpu(raw->i_mtime);
	inode->i_atime.tv_nsec = le32_to_cpu(raw->i_atime_nsec);
	inode->i_ctime.tv_nsec = le32_to_cpu(raw->i_ctime_nsec);
	inode->i_mtime.tv_nsec = le32_to_cpu(raw->i_mtime_nsec);

	F2FS_I(inode)->i_advise = raw->i_advise;
	F2FS_I(inode)->i_flags = le32_to_cpu(raw->i_flags);

	recover_inline_flags(inode, raw);

	if (file_enc_name(inode))
		name = "<encrypted>";
	else
		name = F2FS_INODE(page)->i_name;

	f2fs_msg(inode->i_sb, KERN_NOTICE,
		"recover_inode: ino = %x, name = %s, inline = %x",
			ino_of_node(page), name, raw->i_inline);
}