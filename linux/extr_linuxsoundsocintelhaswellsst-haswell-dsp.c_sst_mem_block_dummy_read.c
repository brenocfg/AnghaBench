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
typedef  int u32 ;
struct sst_mem_block {int size; scalar_t__ offset; struct sst_dsp* dsp; } ;
struct TYPE_2__ {scalar_t__ lpe; } ;
struct sst_dsp {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void sst_mem_block_dummy_read(struct sst_mem_block *block)
{
	u32 size;
	u8 tmp_buf[4];
	struct sst_dsp *sst = block->dsp;

	size = block->size > 4 ? 4 : block->size;
	memcpy_fromio(tmp_buf, sst->addr.lpe + block->offset, size);
}