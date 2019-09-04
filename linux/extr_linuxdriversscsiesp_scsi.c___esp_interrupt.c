#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct esp {int sreg; int ireg; int flags; scalar_t__ rev; scalar_t__ select_state; scalar_t__ event; int sreg2; scalar_t__ active_cmd; int /*<<< orphan*/  host; void* seqreg; int /*<<< orphan*/ * eh_reset; } ;

/* Variables and functions */
 int ESP_DIP ; 
 int ESP_DOP ; 
 scalar_t__ ESP_EVENT_DATA_DONE ; 
 scalar_t__ ESP_EVENT_STATUS ; 
 int ESP_FLAG_RESETTING ; 
 int /*<<< orphan*/  ESP_INTRPT ; 
 int ESP_INTR_IC ; 
 int ESP_INTR_RSEL ; 
 int ESP_INTR_S ; 
 int ESP_INTR_SATN ; 
 int ESP_INTR_SR ; 
 scalar_t__ ESP_SELECT_NONE ; 
 int /*<<< orphan*/  ESP_SSTEP ; 
 int ESP_STAT2_F1BYTE ; 
 int ESP_STAT2_FEMPTY ; 
 int /*<<< orphan*/  ESP_STATUS ; 
 int /*<<< orphan*/  ESP_STATUS2 ; 
 int ESP_STAT_PMASK ; 
 scalar_t__ FASHME ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_check_gross_error (struct esp*) ; 
 int esp_check_spur_intr (struct esp*) ; 
 int /*<<< orphan*/  esp_dump_cmd_log (struct esp*) ; 
 int esp_finish_select (struct esp*) ; 
 int /*<<< orphan*/  esp_log_intr (char*,int,void*,int,int) ; 
 int esp_process_event (struct esp*) ; 
 void* esp_read8 (int /*<<< orphan*/ ) ; 
 int esp_reconnect (struct esp*) ; 
 int /*<<< orphan*/  esp_reset_cleanup (struct esp*) ; 
 int /*<<< orphan*/  esp_schedule_reset (struct esp*) ; 
 int /*<<< orphan*/  hme_read_fifo (struct esp*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void __esp_interrupt(struct esp *esp)
{
	int finish_reset, intr_done;
	u8 phase;

       /*
	* Once INTRPT is read STATUS and SSTEP are cleared.
	*/
	esp->sreg = esp_read8(ESP_STATUS);
	esp->seqreg = esp_read8(ESP_SSTEP);
	esp->ireg = esp_read8(ESP_INTRPT);

	if (esp->flags & ESP_FLAG_RESETTING) {
		finish_reset = 1;
	} else {
		if (esp_check_gross_error(esp))
			return;

		finish_reset = esp_check_spur_intr(esp);
		if (finish_reset < 0)
			return;
	}

	if (esp->ireg & ESP_INTR_SR)
		finish_reset = 1;

	if (finish_reset) {
		esp_reset_cleanup(esp);
		if (esp->eh_reset) {
			complete(esp->eh_reset);
			esp->eh_reset = NULL;
		}
		return;
	}

	phase = (esp->sreg & ESP_STAT_PMASK);
	if (esp->rev == FASHME) {
		if (((phase != ESP_DIP && phase != ESP_DOP) &&
		     esp->select_state == ESP_SELECT_NONE &&
		     esp->event != ESP_EVENT_STATUS &&
		     esp->event != ESP_EVENT_DATA_DONE) ||
		    (esp->ireg & ESP_INTR_RSEL)) {
			esp->sreg2 = esp_read8(ESP_STATUS2);
			if (!(esp->sreg2 & ESP_STAT2_FEMPTY) ||
			    (esp->sreg2 & ESP_STAT2_F1BYTE))
				hme_read_fifo(esp);
		}
	}

	esp_log_intr("intr sreg[%02x] seqreg[%02x] "
		     "sreg2[%02x] ireg[%02x]\n",
		     esp->sreg, esp->seqreg, esp->sreg2, esp->ireg);

	intr_done = 0;

	if (esp->ireg & (ESP_INTR_S | ESP_INTR_SATN | ESP_INTR_IC)) {
		shost_printk(KERN_INFO, esp->host,
			     "unexpected IREG %02x\n", esp->ireg);
		if (esp->ireg & ESP_INTR_IC)
			esp_dump_cmd_log(esp);

		esp_schedule_reset(esp);
	} else {
		if (esp->ireg & ESP_INTR_RSEL) {
			if (esp->active_cmd)
				(void) esp_finish_select(esp);
			intr_done = esp_reconnect(esp);
		} else {
			/* Some combination of FDONE, BSERV, DC. */
			if (esp->select_state != ESP_SELECT_NONE)
				intr_done = esp_finish_select(esp);
		}
	}
	while (!intr_done)
		intr_done = esp_process_event(esp);
}