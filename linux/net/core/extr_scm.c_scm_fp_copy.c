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
struct scm_fp_list {size_t count; int max; int /*<<< orphan*/ * user; struct file** fp; } ;
struct file {int dummy; } ;
struct cmsghdr {int cmsg_len; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int EBADF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCM_MAX_FD ; 
 int /*<<< orphan*/  current_user () ; 
 struct file* fget_raw (int) ; 
 int /*<<< orphan*/ * get_uid (int /*<<< orphan*/ ) ; 
 struct scm_fp_list* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scm_fp_copy(struct cmsghdr *cmsg, struct scm_fp_list **fplp)
{
	int *fdp = (int*)CMSG_DATA(cmsg);
	struct scm_fp_list *fpl = *fplp;
	struct file **fpp;
	int i, num;

	num = (cmsg->cmsg_len - sizeof(struct cmsghdr))/sizeof(int);

	if (num <= 0)
		return 0;

	if (num > SCM_MAX_FD)
		return -EINVAL;

	if (!fpl)
	{
		fpl = kmalloc(sizeof(struct scm_fp_list), GFP_KERNEL);
		if (!fpl)
			return -ENOMEM;
		*fplp = fpl;
		fpl->count = 0;
		fpl->max = SCM_MAX_FD;
		fpl->user = NULL;
	}
	fpp = &fpl->fp[fpl->count];

	if (fpl->count + num > fpl->max)
		return -EINVAL;

	/*
	 *	Verify the descriptors and increment the usage count.
	 */

	for (i=0; i< num; i++)
	{
		int fd = fdp[i];
		struct file *file;

		if (fd < 0 || !(file = fget_raw(fd)))
			return -EBADF;
		*fpp++ = file;
		fpl->count++;
	}

	if (!fpl->user)
		fpl->user = get_uid(current_user());

	return num;
}