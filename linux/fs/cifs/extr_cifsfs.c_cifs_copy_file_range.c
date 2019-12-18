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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  cifs_file_copychunk_range (unsigned int,struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,size_t,unsigned int) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 int /*<<< orphan*/  generic_copy_file_range (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,size_t,unsigned int) ; 
 unsigned int get_xid () ; 

__attribute__((used)) static ssize_t cifs_copy_file_range(struct file *src_file, loff_t off,
				struct file *dst_file, loff_t destoff,
				size_t len, unsigned int flags)
{
	unsigned int xid = get_xid();
	ssize_t rc;

	rc = cifs_file_copychunk_range(xid, src_file, off, dst_file, destoff,
					len, flags);
	free_xid(xid);

	if (rc == -EOPNOTSUPP || rc == -EXDEV)
		rc = generic_copy_file_range(src_file, off, dst_file,
					     destoff, len, flags);
	return rc;
}