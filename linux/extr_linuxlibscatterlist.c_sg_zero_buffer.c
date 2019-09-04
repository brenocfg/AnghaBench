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
struct sg_mapping_iter {int /*<<< orphan*/  addr; int /*<<< orphan*/  length; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 unsigned int SG_MITER_ATOMIC ; 
 unsigned int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_skip (struct sg_mapping_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,struct scatterlist*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

size_t sg_zero_buffer(struct scatterlist *sgl, unsigned int nents,
		       size_t buflen, off_t skip)
{
	unsigned int offset = 0;
	struct sg_mapping_iter miter;
	unsigned int sg_flags = SG_MITER_ATOMIC | SG_MITER_TO_SG;

	sg_miter_start(&miter, sgl, nents, sg_flags);

	if (!sg_miter_skip(&miter, skip))
		return false;

	while (offset < buflen && sg_miter_next(&miter)) {
		unsigned int len;

		len = min(miter.length, buflen - offset);
		memset(miter.addr, 0, len);

		offset += len;
	}

	sg_miter_stop(&miter);
	return offset;
}