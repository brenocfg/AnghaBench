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
struct v9fs_session_info {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct v9fs_session_info* s_fs_info; } ;

/* Variables and functions */

__attribute__((used)) static inline struct v9fs_session_info *v9fs_dentry2v9ses(struct dentry *dentry)
{
	return dentry->d_sb->s_fs_info;
}