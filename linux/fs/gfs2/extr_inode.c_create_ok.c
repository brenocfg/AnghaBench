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
typedef  int /*<<< orphan*/  umode_t ;
typedef  scalar_t__ u32 ;
struct qstr {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_nlink; } ;
struct gfs2_inode {scalar_t__ i_entries; TYPE_1__ i_inode; } ;

/* Variables and functions */
 int EFBIG ; 
 int EMLINK ; 
 int ENOENT ; 
 int MAY_EXEC ; 
 int MAY_WRITE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int gfs2_permission (TYPE_1__*,int) ; 

__attribute__((used)) static int create_ok(struct gfs2_inode *dip, const struct qstr *name,
		     umode_t mode)
{
	int error;

	error = gfs2_permission(&dip->i_inode, MAY_WRITE | MAY_EXEC);
	if (error)
		return error;

	/*  Don't create entries in an unlinked directory  */
	if (!dip->i_inode.i_nlink)
		return -ENOENT;

	if (dip->i_entries == (u32)-1)
		return -EFBIG;
	if (S_ISDIR(mode) && dip->i_inode.i_nlink == (u32)-1)
		return -EMLINK;

	return 0;
}