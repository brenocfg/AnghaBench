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
struct ocfs2_dlm_debug {int /*<<< orphan*/  d_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dlm_debug_free ; 

void ocfs2_put_dlm_debug(struct ocfs2_dlm_debug *dlm_debug)
{
	if (dlm_debug)
		kref_put(&dlm_debug->d_refcnt, ocfs2_dlm_debug_free);
}