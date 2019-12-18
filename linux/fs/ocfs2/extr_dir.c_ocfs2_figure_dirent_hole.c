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
struct ocfs2_dir_entry {int /*<<< orphan*/  name_len; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 unsigned int OCFS2_DIR_REC_LEN (int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ocfs2_figure_dirent_hole(struct ocfs2_dir_entry *de)
{
	unsigned int hole;

	if (le64_to_cpu(de->inode) == 0)
		hole = le16_to_cpu(de->rec_len);
	else
		hole = le16_to_cpu(de->rec_len) -
			OCFS2_DIR_REC_LEN(de->name_len);

	return hole;
}