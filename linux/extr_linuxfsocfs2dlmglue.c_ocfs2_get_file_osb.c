#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {struct ocfs2_file_private* l_priv; } ;
struct ocfs2_file_private {TYPE_3__* fp_file; } ;
struct TYPE_6__ {TYPE_2__* f_mapping; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocfs2_super *ocfs2_get_file_osb(struct ocfs2_lock_res *lockres)
{
	struct ocfs2_file_private *fp = lockres->l_priv;

	return OCFS2_SB(fp->fp_file->f_mapping->host->i_sb);
}