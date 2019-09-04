#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct file* file; } ;
struct splice_desc {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  total_len; int /*<<< orphan*/  pos; TYPE_2__ u; } ;
struct pipe_inode_info {int nrbufs; } ;
struct pipe_buffer {int /*<<< orphan*/  offset; int /*<<< orphan*/  page; } ;
struct file {TYPE_1__* f_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {int (* sendpage ) (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int MSG_MORE ; 
 int MSG_SENDPAGE_NOTLAST ; 
 int SPLICE_F_MORE ; 
 int /*<<< orphan*/  likely (int (*) (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int)) ; 
 int stub1 (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pipe_to_sendpage(struct pipe_inode_info *pipe,
			    struct pipe_buffer *buf, struct splice_desc *sd)
{
	struct file *file = sd->u.file;
	loff_t pos = sd->pos;
	int more;

	if (!likely(file->f_op->sendpage))
		return -EINVAL;

	more = (sd->flags & SPLICE_F_MORE) ? MSG_MORE : 0;

	if (sd->len < sd->total_len && pipe->nrbufs > 1)
		more |= MSG_SENDPAGE_NOTLAST;

	return file->f_op->sendpage(file, buf->page, buf->offset,
				    sd->len, &pos, more);
}