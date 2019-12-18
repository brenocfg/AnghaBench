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
struct TYPE_5__ {int /*<<< orphan*/  ac97_data; TYPE_1__ sr_csr; int /*<<< orphan*/  ac97_cmd; } ;

/* Variables and functions */
 unsigned short ENODEV ; 
 int MPC52xx_PSC_SR_CMDSEND ; 
 int MPC52xx_PSC_SR_DATA_VAL ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 unsigned int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 TYPE_3__* psc_dma ; 
 int spin_event_timeout (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short psc_ac97_read(struct snd_ac97 *ac97, unsigned short reg)
{
	int status;
	unsigned int val;

	mutex_lock(&psc_dma->mutex);

	/* Wait for command send status zero = ready */
	status = spin_event_timeout(!(in_be16(&psc_dma->psc_regs->sr_csr.status) &
				MPC52xx_PSC_SR_CMDSEND), 100, 0);
	if (status == 0) {
		pr_err("timeout on ac97 bus (rdy)\n");
		mutex_unlock(&psc_dma->mutex);
		return -ENODEV;
	}

	/* Force clear the data valid bit */
	in_be32(&psc_dma->psc_regs->ac97_data);

	/* Send the read */
	out_be32(&psc_dma->psc_regs->ac97_cmd, (1<<31) | ((reg & 0x7f) << 24));

	/* Wait for the answer */
	status = spin_event_timeout((in_be16(&psc_dma->psc_regs->sr_csr.status) &
				MPC52xx_PSC_SR_DATA_VAL), 100, 0);
	if (status == 0) {
		pr_err("timeout on ac97 read (val) %x\n",
				in_be16(&psc_dma->psc_regs->sr_csr.status));
		mutex_unlock(&psc_dma->mutex);
		return -ENODEV;
	}
	/* Get the data */
	val = in_be32(&psc_dma->psc_regs->ac97_data);
	if (((val >> 24) & 0x7f) != reg) {
		pr_err("reg echo error on ac97 read\n");
		mutex_unlock(&psc_dma->mutex);
		return -ENODEV;
	}
	val = (val >> 8) & 0xffff;

	mutex_unlock(&psc_dma->mutex);
	return (unsigned short) val;
}