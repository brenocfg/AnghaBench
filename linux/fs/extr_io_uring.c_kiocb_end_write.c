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
struct io_kiocb {int flags; int /*<<< orphan*/  file; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int REQ_F_ISREG ; 
 int /*<<< orphan*/  SB_FREEZE_WRITE ; 
 int /*<<< orphan*/  __sb_writers_acquired (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_end_write (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kiocb_end_write(struct io_kiocb *req)
{
	/*
	 * Tell lockdep we inherited freeze protection from submission
	 * thread.
	 */
	if (req->flags & REQ_F_ISREG) {
		struct inode *inode = file_inode(req->file);

		__sb_writers_acquired(inode->i_sb, SB_FREEZE_WRITE);
	}
	file_end_write(req->file);
}