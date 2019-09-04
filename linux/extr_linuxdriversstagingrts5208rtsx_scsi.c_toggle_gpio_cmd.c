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
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {scalar_t__ ss_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 scalar_t__ RTSX_STAT_SS ; 
 int TRANSPORT_GOOD ; 
 int /*<<< orphan*/  rtsx_disable_aspm (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_exit_ss (struct rtsx_chip*) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toggle_gpio (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int toggle_gpio_cmd(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	u8 gpio = srb->cmnd[2];

	rtsx_disable_aspm(chip);

	if (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) {
		rtsx_exit_ss(chip);
		wait_timeout(100);
	}
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	if (gpio > 3)
		gpio = 1;
	toggle_gpio(chip, gpio);

	return TRANSPORT_GOOD;
}