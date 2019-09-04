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
struct fsg_common {unsigned int fsg_num_buffers; struct fsg_buffhd* buffhds; } ;
struct fsg_buffhd {struct fsg_buffhd* next; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FSG_BUFLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _fsg_common_free_buffers (struct fsg_buffhd*,unsigned int) ; 
 struct fsg_buffhd* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int fsg_common_set_num_buffers(struct fsg_common *common, unsigned int n)
{
	struct fsg_buffhd *bh, *buffhds;
	int i;

	buffhds = kcalloc(n, sizeof(*buffhds), GFP_KERNEL);
	if (!buffhds)
		return -ENOMEM;

	/* Data buffers cyclic list */
	bh = buffhds;
	i = n;
	goto buffhds_first_it;
	do {
		bh->next = bh + 1;
		++bh;
buffhds_first_it:
		bh->buf = kmalloc(FSG_BUFLEN, GFP_KERNEL);
		if (unlikely(!bh->buf))
			goto error_release;
	} while (--i);
	bh->next = buffhds;

	_fsg_common_free_buffers(common->buffhds, common->fsg_num_buffers);
	common->fsg_num_buffers = n;
	common->buffhds = buffhds;

	return 0;

error_release:
	/*
	 * "buf"s pointed to by heads after n - i are NULL
	 * so releasing them won't hurt
	 */
	_fsg_common_free_buffers(buffhds, n);

	return -ENOMEM;
}