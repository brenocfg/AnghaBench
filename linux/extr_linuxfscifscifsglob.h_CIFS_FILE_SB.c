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
struct file {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 TYPE_1__* file_inode (struct file*) ; 

__attribute__((used)) static inline struct cifs_sb_info *
CIFS_FILE_SB(struct file *file)
{
	return CIFS_SB(file_inode(file)->i_sb);
}