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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_ORPHAN_SCAN ; 
 int /*<<< orphan*/  ocfs2_build_lock_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_common (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_once (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_orphan_scan_lops ; 

__attribute__((used)) static void ocfs2_orphan_scan_lock_res_init(struct ocfs2_lock_res *res,
					    struct ocfs2_super *osb)
{
	ocfs2_lock_res_init_once(res);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_ORPHAN_SCAN, 0, 0, res->l_name);
	ocfs2_lock_res_init_common(osb, res, OCFS2_LOCK_TYPE_ORPHAN_SCAN,
				   &ocfs2_orphan_scan_lops, osb);
}