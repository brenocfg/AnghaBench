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
struct TYPE_2__ {void* low; void* high; } ;
union acp_dma_count {int /*<<< orphan*/  bytescount; TYPE_1__ bcount; } ;
typedef  int /*<<< orphan*/  u64 ;
struct audio_substream_data {int /*<<< orphan*/  byte_cnt_low_reg_offset; int /*<<< orphan*/  acp_mmio; int /*<<< orphan*/  byte_cnt_high_reg_offset; } ;

/* Variables and functions */
 void* acp_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 acp_get_byte_count(struct audio_substream_data *rtd)
{
	union acp_dma_count byte_count;

	byte_count.bcount.high = acp_reg_read(rtd->acp_mmio,
					      rtd->byte_cnt_high_reg_offset);
	byte_count.bcount.low  = acp_reg_read(rtd->acp_mmio,
					      rtd->byte_cnt_low_reg_offset);
	return byte_count.bytescount;
}