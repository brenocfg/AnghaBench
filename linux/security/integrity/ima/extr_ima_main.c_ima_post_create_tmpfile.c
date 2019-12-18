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
struct integrity_iint_cache {int /*<<< orphan*/  ima_file_status; int /*<<< orphan*/  atomic_flags; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_CHECK ; 
 int /*<<< orphan*/  IMA_UPDATE_XATTR ; 
 int /*<<< orphan*/  INTEGRITY_PASS ; 
 int /*<<< orphan*/  MAY_ACCESS ; 
 int ima_must_appraise (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct integrity_iint_cache* integrity_inode_get (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ima_post_create_tmpfile(struct inode *inode)
{
	struct integrity_iint_cache *iint;
	int must_appraise;

	must_appraise = ima_must_appraise(inode, MAY_ACCESS, FILE_CHECK);
	if (!must_appraise)
		return;

	/* Nothing to do if we can't allocate memory */
	iint = integrity_inode_get(inode);
	if (!iint)
		return;

	/* needed for writing the security xattrs */
	set_bit(IMA_UPDATE_XATTR, &iint->atomic_flags);
	iint->ima_file_status = INTEGRITY_PASS;
}