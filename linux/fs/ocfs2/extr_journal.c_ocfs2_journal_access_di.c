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
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int __ocfs2_journal_access (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  di_triggers ; 

int ocfs2_journal_access_di(handle_t *handle, struct ocfs2_caching_info *ci,
			    struct buffer_head *bh, int type)
{
	return __ocfs2_journal_access(handle, ci, bh, &di_triggers, type);
}