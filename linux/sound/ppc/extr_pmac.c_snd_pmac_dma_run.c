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
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void snd_pmac_dma_run(struct pmac_stream *rec, int status)
{
	out_le32(&rec->dma->control, status | (status << 16));
}