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
struct TYPE_2__ {scalar_t__ fw_ver; int /*<<< orphan*/ * wait; } ;
struct snic {int /*<<< orphan*/  snic_lock; TYPE_1__ fwinfo; int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snic_queue_exch_ver_req (struct snic*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
snic_get_conf(struct snic *snic)
{
	DECLARE_COMPLETION_ONSTACK(wait);
	unsigned long flags;
	int ret;
	int nr_retries = 3;

	SNIC_HOST_INFO(snic->shost, "Retrieving snic params.\n");
	spin_lock_irqsave(&snic->snic_lock, flags);
	memset(&snic->fwinfo, 0, sizeof(snic->fwinfo));
	snic->fwinfo.wait = &wait;
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	/* Additional delay to handle HW Resource initialization. */
	msleep(50);

	/*
	 * Exch ver req can be ignored by FW, if HW Resource initialization
	 * is in progress, Hence retry.
	 */
	do {
		ret = snic_queue_exch_ver_req(snic);
		if (ret)
			return ret;

		wait_for_completion_timeout(&wait, msecs_to_jiffies(2000));
		spin_lock_irqsave(&snic->snic_lock, flags);
		ret = (snic->fwinfo.fw_ver != 0) ? 0 : -ETIMEDOUT;
		if (ret)
			SNIC_HOST_ERR(snic->shost,
				      "Failed to retrieve snic params,\n");

		/* Unset fwinfo.wait, on success or on last retry */
		if (ret == 0 || nr_retries == 1)
			snic->fwinfo.wait = NULL;

		spin_unlock_irqrestore(&snic->snic_lock, flags);
	} while (ret && --nr_retries);

	return ret;
}