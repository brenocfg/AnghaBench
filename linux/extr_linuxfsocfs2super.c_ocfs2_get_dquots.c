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
struct inode {int dummy; } ;
struct dquot {int dummy; } ;
struct TYPE_2__ {struct dquot** i_dquot; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 

__attribute__((used)) static struct dquot **ocfs2_get_dquots(struct inode *inode)
{
	return OCFS2_I(inode)->i_dquot;
}