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
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_name_len; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 unsigned int GFS2_DIRENT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct gfs2_dirent* do_init_dirent (struct inode*,struct gfs2_dirent*,struct qstr const*,struct buffer_head*,unsigned int) ; 
 int /*<<< orphan*/  gfs2_dirent_sentinel (struct gfs2_dirent*) ; 

__attribute__((used)) static struct gfs2_dirent *gfs2_init_dirent(struct inode *inode,
					    struct gfs2_dirent *dent,
					    const struct qstr *name,
					    struct buffer_head *bh)
{
	unsigned offset = 0;

	if (!gfs2_dirent_sentinel(dent))
		offset = GFS2_DIRENT_SIZE(be16_to_cpu(dent->de_name_len));
	return do_init_dirent(inode, dent, name, bh, offset);
}