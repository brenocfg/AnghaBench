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
 int FLUSH ; 
 int PAUSE ; 
 int RUN ; 
 int WAKE ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_pmac_wait_ack (struct pmac_stream*) ; 

__attribute__((used)) static inline void snd_pmac_dma_stop(struct pmac_stream *rec)
{
	out_le32(&rec->dma->control, (RUN|WAKE|FLUSH|PAUSE) << 16);
	snd_pmac_wait_ack(rec);
}