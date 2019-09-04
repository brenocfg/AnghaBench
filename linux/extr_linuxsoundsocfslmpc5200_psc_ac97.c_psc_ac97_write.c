#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_ac97 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_2__* psc_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  ac97_cmd; TYPE_1__ sr_csr; } ;

/* Variables and functions */
 int MPC52xx_PSC_SR_CMDSEND ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_3__* psc_dma ; 
 int spin_event_timeout (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psc_ac97_write(struct snd_ac97 *ac97,
				unsigned short reg, unsigned short val)
{
	int status;

	mutex_lock(&psc_dma->mutex);

	/* Wait for command status zero = ready */
	status = spin_event_timeout(!(in_be16(&psc_dma->psc_regs->sr_csr.status) &
				MPC52xx_PSC_SR_CMDSEND), 100, 0);
	if (status == 0) {
		pr_err("timeout on ac97 bus (write)\n");
		goto out;
	}
	/* Write data */
	out_be32(&psc_dma->psc_regs->ac97_cmd,
			((reg & 0x7f) << 24) | (val << 8));

 out:
	mutex_unlock(&psc_dma->mutex);
}