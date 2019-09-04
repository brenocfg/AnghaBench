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
typedef  int /*<<< orphan*/  u64 ;
struct scatterlist {int dummy; } ;
struct pqi_sg_descriptor {int /*<<< orphan*/  flags; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_le32 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static inline void pqi_set_sg_descriptor(
	struct pqi_sg_descriptor *sg_descriptor, struct scatterlist *sg)
{
	u64 address = (u64)sg_dma_address(sg);
	unsigned int length = sg_dma_len(sg);

	put_unaligned_le64(address, &sg_descriptor->address);
	put_unaligned_le32(length, &sg_descriptor->length);
	put_unaligned_le32(0, &sg_descriptor->flags);
}