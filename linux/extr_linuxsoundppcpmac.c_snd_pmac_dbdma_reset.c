#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dma; } ;
struct snd_pmac {TYPE_2__ capture; TYPE_2__ playback; } ;
struct TYPE_3__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int DEAD ; 
 int FLUSH ; 
 int PAUSE ; 
 int RUN ; 
 int WAKE ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_pmac_wait_ack (TYPE_2__*) ; 

__attribute__((used)) static void snd_pmac_dbdma_reset(struct snd_pmac *chip)
{
	out_le32(&chip->playback.dma->control, (RUN|PAUSE|FLUSH|WAKE|DEAD) << 16);
	snd_pmac_wait_ack(&chip->playback);
	out_le32(&chip->capture.dma->control, (RUN|PAUSE|FLUSH|WAKE|DEAD) << 16);
	snd_pmac_wait_ack(&chip->capture);
}