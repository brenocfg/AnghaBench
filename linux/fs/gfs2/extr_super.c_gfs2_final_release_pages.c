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
struct inode {int /*<<< orphan*/  i_data; } ;
struct gfs2_inode {struct gfs2_glock* i_gl; struct inode i_inode; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_revokes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLF_DIRTY ; 
 int /*<<< orphan*/  GLF_LFLUSH ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_final_release_pages(struct gfs2_inode *ip)
{
	struct inode *inode = &ip->i_inode;
	struct gfs2_glock *gl = ip->i_gl;

	truncate_inode_pages(gfs2_glock2aspace(ip->i_gl), 0);
	truncate_inode_pages(&inode->i_data, 0);

	if (atomic_read(&gl->gl_revokes) == 0) {
		clear_bit(GLF_LFLUSH, &gl->gl_flags);
		clear_bit(GLF_DIRTY, &gl->gl_flags);
	}
}