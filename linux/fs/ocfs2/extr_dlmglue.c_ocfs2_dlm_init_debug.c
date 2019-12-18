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
struct ocfs2_super {int /*<<< orphan*/  osb_debug_root; struct ocfs2_dlm_debug* osb_dlm_debug; } ;
struct ocfs2_dlm_debug {int /*<<< orphan*/  d_filter_secs; } ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_dlm_debug_fops ; 

__attribute__((used)) static void ocfs2_dlm_init_debug(struct ocfs2_super *osb)
{
	struct ocfs2_dlm_debug *dlm_debug = osb->osb_dlm_debug;

	debugfs_create_file("locking_state", S_IFREG|S_IRUSR,
			    osb->osb_debug_root, osb, &ocfs2_dlm_debug_fops);

	debugfs_create_u32("locking_filter", 0600, osb->osb_debug_root,
			   &dlm_debug->d_filter_secs);
}