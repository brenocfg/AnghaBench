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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sb_lkid; } ;
struct ocfs2_dlm_lksb {TYPE_1__ lksb_fsdlm; } ;
struct ocfs2_cluster_connection {int /*<<< orphan*/  cc_lockspace; } ;

/* Variables and functions */
 int dlm_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct ocfs2_dlm_lksb*) ; 

__attribute__((used)) static int user_dlm_unlock(struct ocfs2_cluster_connection *conn,
			   struct ocfs2_dlm_lksb *lksb,
			   u32 flags)
{
	int ret;

	ret = dlm_unlock(conn->cc_lockspace, lksb->lksb_fsdlm.sb_lkid,
			 flags, &lksb->lksb_fsdlm, lksb);
	return ret;
}