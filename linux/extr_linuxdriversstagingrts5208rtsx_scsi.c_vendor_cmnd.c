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
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
#define  GET_BUS_WIDTH 137 
#define  GET_SD_CSD 136 
#define  READ_EEPROM 135 
#define  READ_MEM 134 
#define  READ_STATUS 133 
#define  SCSI_APP_CMD 132 
 int /*<<< orphan*/  SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
#define  SPI_VENDOR_COMMAND 131 
#define  TOGGLE_GPIO 130 
 int TRANSPORT_FAILED ; 
#define  WRITE_EEPROM 129 
#define  WRITE_MEM 128 
 int app_cmd (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int get_card_bus_width (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int get_sd_csd (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_eeprom (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_mem (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_status (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spi_vendor_cmd (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int toggle_gpio_cmd (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int write_eeprom (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int write_mem (struct scsi_cmnd*,struct rtsx_chip*) ; 

__attribute__((used)) static int vendor_cmnd(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int result;

	switch (srb->cmnd[1]) {
	case READ_STATUS:
		result = read_status(srb, chip);
		break;

	case READ_MEM:
		result = read_mem(srb, chip);
		break;

	case WRITE_MEM:
		result = write_mem(srb, chip);
		break;

	case READ_EEPROM:
		result = read_eeprom(srb, chip);
		break;

	case WRITE_EEPROM:
		result = write_eeprom(srb, chip);
		break;

	case TOGGLE_GPIO:
		result = toggle_gpio_cmd(srb, chip);
		break;

	case GET_SD_CSD:
		result = get_sd_csd(srb, chip);
		break;

	case GET_BUS_WIDTH:
		result = get_card_bus_width(srb, chip);
		break;

	case SCSI_APP_CMD:
		result = app_cmd(srb, chip);
		break;

	case SPI_VENDOR_COMMAND:
		result = spi_vendor_cmd(srb, chip);
		break;

	default:
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	return result;
}