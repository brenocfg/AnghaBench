#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct mmpin {int dummy; } ;
struct TYPE_7__ {struct mmpin z_mmp; } ;
struct rds_msg_zcopy_info {TYPE_3__ znotif; int /*<<< orphan*/  rs_zcookie_next; } ;
struct TYPE_8__ {int op_nents; TYPE_3__* op_mmp_znotifier; struct scatterlist* op_sg; } ;
struct TYPE_5__ {int /*<<< orphan*/  h_len; } ;
struct TYPE_6__ {TYPE_1__ i_hdr; } ;
struct rds_message {TYPE_4__ data; TYPE_2__ m_inc; } ;
struct page {int dummy; } ;
struct iov_iter {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,scalar_t__) ; 
 int iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_get_pages (struct iov_iter*,struct page**,int /*<<< orphan*/ ,int,size_t*) ; 
 int /*<<< orphan*/  kfree (struct rds_msg_zcopy_info*) ; 
 struct rds_msg_zcopy_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mm_account_pinned_pages (struct mmpin*,int) ; 
 int /*<<< orphan*/  mm_unaccount_pinned_pages (struct mmpin*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,scalar_t__,size_t) ; 

__attribute__((used)) static int rds_message_zcopy_from_user(struct rds_message *rm, struct iov_iter *from)
{
	struct scatterlist *sg;
	int ret = 0;
	int length = iov_iter_count(from);
	int total_copied = 0;
	struct rds_msg_zcopy_info *info;

	rm->m_inc.i_hdr.h_len = cpu_to_be32(iov_iter_count(from));

	/*
	 * now allocate and copy in the data payload.
	 */
	sg = rm->data.op_sg;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	INIT_LIST_HEAD(&info->rs_zcookie_next);
	rm->data.op_mmp_znotifier = &info->znotif;
	if (mm_account_pinned_pages(&rm->data.op_mmp_znotifier->z_mmp,
				    length)) {
		ret = -ENOMEM;
		goto err;
	}
	while (iov_iter_count(from)) {
		struct page *pages;
		size_t start;
		ssize_t copied;

		copied = iov_iter_get_pages(from, &pages, PAGE_SIZE,
					    1, &start);
		if (copied < 0) {
			struct mmpin *mmp;
			int i;

			for (i = 0; i < rm->data.op_nents; i++)
				put_page(sg_page(&rm->data.op_sg[i]));
			mmp = &rm->data.op_mmp_znotifier->z_mmp;
			mm_unaccount_pinned_pages(mmp);
			ret = -EFAULT;
			goto err;
		}
		total_copied += copied;
		iov_iter_advance(from, copied);
		length -= copied;
		sg_set_page(sg, pages, copied, start);
		rm->data.op_nents++;
		sg++;
	}
	WARN_ON_ONCE(length != 0);
	return ret;
err:
	kfree(info);
	rm->data.op_mmp_znotifier = NULL;
	return ret;
}