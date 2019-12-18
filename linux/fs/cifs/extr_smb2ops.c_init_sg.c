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
typedef  int /*<<< orphan*/  u8 ;
struct smb_rqst {unsigned int rq_nvec; unsigned int rq_npages; int /*<<< orphan*/ * rq_pages; TYPE_1__* rq_iov; } ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SMB2_SIGNATURE_SIZE ; 
 struct scatterlist* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rqst_page_get_length (struct smb_rqst*,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  smb2_sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static struct scatterlist *
init_sg(int num_rqst, struct smb_rqst *rqst, u8 *sign)
{
	unsigned int sg_len;
	struct scatterlist *sg;
	unsigned int i;
	unsigned int j;
	unsigned int idx = 0;
	int skip;

	sg_len = 1;
	for (i = 0; i < num_rqst; i++)
		sg_len += rqst[i].rq_nvec + rqst[i].rq_npages;

	sg = kmalloc_array(sg_len, sizeof(struct scatterlist), GFP_KERNEL);
	if (!sg)
		return NULL;

	sg_init_table(sg, sg_len);
	for (i = 0; i < num_rqst; i++) {
		for (j = 0; j < rqst[i].rq_nvec; j++) {
			/*
			 * The first rqst has a transform header where the
			 * first 20 bytes are not part of the encrypted blob
			 */
			skip = (i == 0) && (j == 0) ? 20 : 0;
			smb2_sg_set_buf(&sg[idx++],
					rqst[i].rq_iov[j].iov_base + skip,
					rqst[i].rq_iov[j].iov_len - skip);
			}

		for (j = 0; j < rqst[i].rq_npages; j++) {
			unsigned int len, offset;

			rqst_page_get_length(&rqst[i], j, &len, &offset);
			sg_set_page(&sg[idx++], rqst[i].rq_pages[j], len, offset);
		}
	}
	smb2_sg_set_buf(&sg[idx], sign, SMB2_SIGNATURE_SIZE);
	return sg;
}