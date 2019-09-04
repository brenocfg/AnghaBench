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
struct ocfs2_super {int /*<<< orphan*/  osb_dlm_debug; } ;
struct TYPE_2__ {int /*<<< orphan*/  l_debug_list; } ;
struct ocfs2_dlm_seq_priv {int /*<<< orphan*/  p_dlm_debug; TYPE_1__ p_iter_res; } ;
struct inode {struct ocfs2_super* i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ocfs2_dlm_seq_priv* __seq_open_private (struct file*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_add_lockres_tracking (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dlm_seq_ops ; 
 int /*<<< orphan*/  ocfs2_get_dlm_debug (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dlm_debug_open(struct inode *inode, struct file *file)
{
	struct ocfs2_dlm_seq_priv *priv;
	struct ocfs2_super *osb;

	priv = __seq_open_private(file, &ocfs2_dlm_seq_ops, sizeof(*priv));
	if (!priv) {
		mlog_errno(-ENOMEM);
		return -ENOMEM;
	}

	osb = inode->i_private;
	ocfs2_get_dlm_debug(osb->osb_dlm_debug);
	priv->p_dlm_debug = osb->osb_dlm_debug;
	INIT_LIST_HEAD(&priv->p_iter_res.l_debug_list);

	ocfs2_add_lockres_tracking(&priv->p_iter_res,
				   priv->p_dlm_debug);

	return 0;
}