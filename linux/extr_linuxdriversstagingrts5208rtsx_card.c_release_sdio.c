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
struct rtsx_chip {scalar_t__ sd_io; scalar_t__ chip_insert_with_sdio; } ;

/* Variables and functions */
 int CARD_STOP ; 
 scalar_t__ CHECK_PID (struct rtsx_chip*,int) ; 
 int SDIO_CD_CTRL ; 
 int SDIO_CTRL ; 
 int SD_CLR_ERR ; 
 int SD_STOP ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int,int,int) ; 

__attribute__((used)) static void release_sdio(struct rtsx_chip *chip)
{
	if (chip->sd_io) {
		rtsx_write_register(chip, CARD_STOP, SD_STOP | SD_CLR_ERR,
				    SD_STOP | SD_CLR_ERR);

		if (chip->chip_insert_with_sdio) {
			chip->chip_insert_with_sdio = 0;

			if (CHECK_PID(chip, 0x5288))
				rtsx_write_register(chip, 0xFE5A, 0x08, 0x00);
			else
				rtsx_write_register(chip, 0xFE70, 0x80, 0x00);
		}

		rtsx_write_register(chip, SDIO_CTRL, SDIO_CD_CTRL, 0);
		chip->sd_io = 0;
	}
}