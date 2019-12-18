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
struct file {TYPE_1__* f_op; int /*<<< orphan*/  f_mapping; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_2__ {int (* flush ) (struct file*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct file* ecryptfs_file_to_lower (struct file*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecryptfs_flush(struct file *file, fl_owner_t td)
{
	struct file *lower_file = ecryptfs_file_to_lower(file);

	if (lower_file->f_op->flush) {
		filemap_write_and_wait(file->f_mapping);
		return lower_file->f_op->flush(lower_file, td);
	}

	return 0;
}