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
struct v9fs_session_info {int dummy; } ;
struct super_block {struct v9fs_session_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  kfree (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  v9fs_session_cancel (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_session_close (struct v9fs_session_info*) ; 

__attribute__((used)) static void v9fs_kill_super(struct super_block *s)
{
	struct v9fs_session_info *v9ses = s->s_fs_info;

	p9_debug(P9_DEBUG_VFS, " %p\n", s);

	kill_anon_super(s);

	v9fs_session_cancel(v9ses);
	v9fs_session_close(v9ses);
	kfree(v9ses);
	s->s_fs_info = NULL;
	p9_debug(P9_DEBUG_VFS, "exiting kill_super\n");
}