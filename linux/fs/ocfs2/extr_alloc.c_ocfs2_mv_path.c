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
struct ocfs2_path {TYPE_1__* p_node; } ;
struct TYPE_2__ {int /*<<< orphan*/ * el; int /*<<< orphan*/ * bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_MAX_PATH_DEPTH ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 scalar_t__ path_root_access (struct ocfs2_path*) ; 
 scalar_t__ path_root_bh (struct ocfs2_path*) ; 

__attribute__((used)) static void ocfs2_mv_path(struct ocfs2_path *dest, struct ocfs2_path *src)
{
	int i;

	BUG_ON(path_root_bh(dest) != path_root_bh(src));
	BUG_ON(path_root_access(dest) != path_root_access(src));

	for(i = 1; i < OCFS2_MAX_PATH_DEPTH; i++) {
		brelse(dest->p_node[i].bh);

		dest->p_node[i].bh = src->p_node[i].bh;
		dest->p_node[i].el = src->p_node[i].el;

		src->p_node[i].bh = NULL;
		src->p_node[i].el = NULL;
	}
}