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
struct sg_mapping_iter {void* addr; int /*<<< orphan*/  length; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 unsigned int SG_MITER_ATOMIC ; 
 unsigned int SG_MITER_FROM_SG ; 
 unsigned int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 unsigned int min (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_skip (struct sg_mapping_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,struct scatterlist*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

size_t sg_copy_buffer(struct scatterlist *sgl, unsigned int nents, void *buf,
		      size_t buflen, off_t skip, bool to_buffer)
{
	unsigned int offset = 0;
	struct sg_mapping_iter miter;
	unsigned int sg_flags = SG_MITER_ATOMIC;

	if (to_buffer)
		sg_flags |= SG_MITER_FROM_SG;
	else
		sg_flags |= SG_MITER_TO_SG;

	sg_miter_start(&miter, sgl, nents, sg_flags);

	if (!sg_miter_skip(&miter, skip))
		return false;

	while ((offset < buflen) && sg_miter_next(&miter)) {
		unsigned int len;

		len = min(miter.length, buflen - offset);

		if (to_buffer)
			memcpy(buf + offset, miter.addr, len);
		else
			memcpy(miter.addr, buf + offset, len);

		offset += len;
	}

	sg_miter_stop(&miter);

	return offset;
}