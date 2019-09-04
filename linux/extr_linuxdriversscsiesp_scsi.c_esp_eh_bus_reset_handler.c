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
struct scsi_cmnd {TYPE_2__* device; } ;
struct esp {TYPE_1__* host; struct completion* eh_reset; int /*<<< orphan*/  flags; } ;
struct completion {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_CMD_RS ; 
 int /*<<< orphan*/  ESP_FLAG_RESETTING ; 
 int FAILED ; 
 int HZ ; 
 int SUCCESS ; 
 int /*<<< orphan*/  esp_bus_reset_settle ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 struct esp* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ssleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int) ; 

__attribute__((used)) static int esp_eh_bus_reset_handler(struct scsi_cmnd *cmd)
{
	struct esp *esp = shost_priv(cmd->device->host);
	struct completion eh_reset;
	unsigned long flags;

	init_completion(&eh_reset);

	spin_lock_irqsave(esp->host->host_lock, flags);

	esp->eh_reset = &eh_reset;

	/* XXX This is too simple... We should add lots of
	 * XXX checks here so that if we find that the chip is
	 * XXX very wedged we return failure immediately so
	 * XXX that we can perform a full chip reset.
	 */
	esp->flags |= ESP_FLAG_RESETTING;
	scsi_esp_cmd(esp, ESP_CMD_RS);

	spin_unlock_irqrestore(esp->host->host_lock, flags);

	ssleep(esp_bus_reset_settle);

	if (!wait_for_completion_timeout(&eh_reset, 5 * HZ)) {
		spin_lock_irqsave(esp->host->host_lock, flags);
		esp->eh_reset = NULL;
		spin_unlock_irqrestore(esp->host->host_lock, flags);

		return FAILED;
	}

	return SUCCESS;
}