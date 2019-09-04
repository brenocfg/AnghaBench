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
struct dquot {int dummy; } ;

/* Variables and functions */
 int __ocfs2_sync_dquot (struct dquot*,int) ; 

__attribute__((used)) static inline int ocfs2_global_release_dquot(struct dquot *dquot)
{
	return __ocfs2_sync_dquot(dquot, 1);
}