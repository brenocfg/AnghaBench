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
struct pmac_stream {TYPE_1__* dma; } ;
struct pmac_dbdma {int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void snd_pmac_dma_set_command(struct pmac_stream *rec, struct pmac_dbdma *cmd)
{
	out_le32(&rec->dma->cmdptr, cmd->addr);
}