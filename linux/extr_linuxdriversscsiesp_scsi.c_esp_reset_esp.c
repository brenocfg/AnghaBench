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
typedef  int u8 ;
typedef  int u32 ;
struct esp {int rev; int max_period; int ccycle; int min_period; int config4; int config1; int config2; int prev_cfg3; int scsi_id; int radelay; int flags; int cfact; int prev_stp; int prev_soff; int neg_defp; TYPE_1__* target; } ;
struct TYPE_2__ {int esp_config3; } ;

/* Variables and functions */
#define  ESP100 134 
#define  ESP100A 133 
#define  ESP236 132 
 int /*<<< orphan*/  ESP_CFACT ; 
 int /*<<< orphan*/  ESP_CFG1 ; 
 int /*<<< orphan*/  ESP_CFG2 ; 
 int /*<<< orphan*/  ESP_CFG3 ; 
 int /*<<< orphan*/  ESP_CFG4 ; 
 int ESP_CMD_DMA ; 
 int ESP_CMD_NULL ; 
 int ESP_CMD_RC ; 
 int ESP_CONFIG2_FENAB ; 
 int ESP_CONFIG2_HME32 ; 
 int ESP_CONFIG2_HMEFENAB ; 
 int ESP_CONFIG3_FCLK ; 
 int ESP_CONFIG3_FCLOCK ; 
 int ESP_CONFIG3_IDBIT3 ; 
 int ESP_CONFIG3_OBPUSH ; 
 int ESP_CONFIG4_GE1 ; 
 int ESP_FLAG_DIFFERENTIAL ; 
 int /*<<< orphan*/  ESP_INTRPT ; 
 int /*<<< orphan*/  ESP_SOFF ; 
 int /*<<< orphan*/  ESP_STP ; 
 int /*<<< orphan*/  ESP_TIMEO ; 
 int /*<<< orphan*/  ESP_UID ; 
#define  FAS100A 131 
#define  FAS236 130 
#define  FASHME 129 
 int FAST ; 
#define  PCSCSI 128 
 int esp_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_set_all_config3 (struct esp*,int) ; 
 int /*<<< orphan*/  esp_write8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void esp_reset_esp(struct esp *esp)
{
	u8 family_code, version;

	/* Now reset the ESP chip */
	scsi_esp_cmd(esp, ESP_CMD_RC);
	scsi_esp_cmd(esp, ESP_CMD_NULL | ESP_CMD_DMA);
	if (esp->rev == FAST)
		esp_write8(ESP_CONFIG2_FENAB, ESP_CFG2);
	scsi_esp_cmd(esp, ESP_CMD_NULL | ESP_CMD_DMA);

	/* This is the only point at which it is reliable to read
	 * the ID-code for a fast ESP chip variants.
	 */
	esp->max_period = ((35 * esp->ccycle) / 1000);
	if (esp->rev == FAST) {
		version = esp_read8(ESP_UID);
		family_code = (version & 0xf8) >> 3;
		if (family_code == 0x02)
			esp->rev = FAS236;
		else if (family_code == 0x0a)
			esp->rev = FASHME; /* Version is usually '5'. */
		else
			esp->rev = FAS100A;
		esp->min_period = ((4 * esp->ccycle) / 1000);
	} else {
		esp->min_period = ((5 * esp->ccycle) / 1000);
	}
	if (esp->rev == FAS236) {
		/*
		 * The AM53c974 chip returns the same ID as FAS236;
		 * try to configure glitch eater.
		 */
		u8 config4 = ESP_CONFIG4_GE1;
		esp_write8(config4, ESP_CFG4);
		config4 = esp_read8(ESP_CFG4);
		if (config4 & ESP_CONFIG4_GE1) {
			esp->rev = PCSCSI;
			esp_write8(esp->config4, ESP_CFG4);
		}
	}
	esp->max_period = (esp->max_period + 3)>>2;
	esp->min_period = (esp->min_period + 3)>>2;

	esp_write8(esp->config1, ESP_CFG1);
	switch (esp->rev) {
	case ESP100:
		/* nothing to do */
		break;

	case ESP100A:
		esp_write8(esp->config2, ESP_CFG2);
		break;

	case ESP236:
		/* Slow 236 */
		esp_write8(esp->config2, ESP_CFG2);
		esp->prev_cfg3 = esp->target[0].esp_config3;
		esp_write8(esp->prev_cfg3, ESP_CFG3);
		break;

	case FASHME:
		esp->config2 |= (ESP_CONFIG2_HME32 | ESP_CONFIG2_HMEFENAB);
		/* fallthrough... */

	case FAS236:
	case PCSCSI:
		/* Fast 236, AM53c974 or HME */
		esp_write8(esp->config2, ESP_CFG2);
		if (esp->rev == FASHME) {
			u8 cfg3 = esp->target[0].esp_config3;

			cfg3 |= ESP_CONFIG3_FCLOCK | ESP_CONFIG3_OBPUSH;
			if (esp->scsi_id >= 8)
				cfg3 |= ESP_CONFIG3_IDBIT3;
			esp_set_all_config3(esp, cfg3);
		} else {
			u32 cfg3 = esp->target[0].esp_config3;

			cfg3 |= ESP_CONFIG3_FCLK;
			esp_set_all_config3(esp, cfg3);
		}
		esp->prev_cfg3 = esp->target[0].esp_config3;
		esp_write8(esp->prev_cfg3, ESP_CFG3);
		if (esp->rev == FASHME) {
			esp->radelay = 80;
		} else {
			if (esp->flags & ESP_FLAG_DIFFERENTIAL)
				esp->radelay = 0;
			else
				esp->radelay = 96;
		}
		break;

	case FAS100A:
		/* Fast 100a */
		esp_write8(esp->config2, ESP_CFG2);
		esp_set_all_config3(esp,
				    (esp->target[0].esp_config3 |
				     ESP_CONFIG3_FCLOCK));
		esp->prev_cfg3 = esp->target[0].esp_config3;
		esp_write8(esp->prev_cfg3, ESP_CFG3);
		esp->radelay = 32;
		break;

	default:
		break;
	}

	/* Reload the configuration registers */
	esp_write8(esp->cfact, ESP_CFACT);

	esp->prev_stp = 0;
	esp_write8(esp->prev_stp, ESP_STP);

	esp->prev_soff = 0;
	esp_write8(esp->prev_soff, ESP_SOFF);

	esp_write8(esp->neg_defp, ESP_TIMEO);

	/* Eat any bitrot in the chip */
	esp_read8(ESP_INTRPT);
	udelay(100);
}