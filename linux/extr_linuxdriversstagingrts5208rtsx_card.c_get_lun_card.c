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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_chip {int card_ready; int* lun2card; } ;

/* Variables and functions */
 int MS_CARD ; 
 int SD_CARD ; 
 int XD_CARD ; 

u8 get_lun_card(struct rtsx_chip *chip, unsigned int lun)
{
	if ((chip->card_ready & chip->lun2card[lun]) == XD_CARD)
		return (u8)XD_CARD;
	else if ((chip->card_ready & chip->lun2card[lun]) == SD_CARD)
		return (u8)SD_CARD;
	else if ((chip->card_ready & chip->lun2card[lun]) == MS_CARD)
		return (u8)MS_CARD;

	return 0;
}