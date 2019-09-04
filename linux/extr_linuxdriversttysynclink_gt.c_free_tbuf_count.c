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
struct slgt_info {unsigned int tbuf_current; unsigned int tbuf_count; int /*<<< orphan*/ * tbufs; } ;

/* Variables and functions */
 int BIT0 ; 
 int /*<<< orphan*/  TDCSR ; 
 scalar_t__ desc_count (int /*<<< orphan*/ ) ; 
 int rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int free_tbuf_count(struct slgt_info *info)
{
	unsigned int count = 0;
	unsigned int i = info->tbuf_current;

	do
	{
		if (desc_count(info->tbufs[i]))
			break; /* buffer in use */
		++count;
		if (++i == info->tbuf_count)
			i=0;
	} while (i != info->tbuf_current);

	/* if tx DMA active, last zero count buffer is in use */
	if (count && (rd_reg32(info, TDCSR) & BIT0))
		--count;

	return count;
}