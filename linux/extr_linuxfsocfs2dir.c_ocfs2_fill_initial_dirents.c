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
struct ocfs2_dir_entry {int name_len; int /*<<< orphan*/  name; void* rec_len; void* inode; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_DIR_REC_LEN (int) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  ocfs2_set_de_type (struct ocfs2_dir_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct ocfs2_dir_entry *ocfs2_fill_initial_dirents(struct inode *inode,
							  struct inode *parent,
							  char *start,
							  unsigned int size)
{
	struct ocfs2_dir_entry *de = (struct ocfs2_dir_entry *)start;

	de->inode = cpu_to_le64(OCFS2_I(inode)->ip_blkno);
	de->name_len = 1;
	de->rec_len =
		cpu_to_le16(OCFS2_DIR_REC_LEN(de->name_len));
	strcpy(de->name, ".");
	ocfs2_set_de_type(de, S_IFDIR);

	de = (struct ocfs2_dir_entry *) ((char *)de + le16_to_cpu(de->rec_len));
	de->inode = cpu_to_le64(OCFS2_I(parent)->ip_blkno);
	de->rec_len = cpu_to_le16(size - OCFS2_DIR_REC_LEN(1));
	de->name_len = 2;
	strcpy(de->name, "..");
	ocfs2_set_de_type(de, S_IFDIR);

	return de;
}