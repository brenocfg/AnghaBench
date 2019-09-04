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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STOP ; 
 int XD_CLR_ERR ; 
 int XD_STOP ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void rtsx_clear_xd_error(struct rtsx_chip *chip)
{
	rtsx_write_register(chip, CARD_STOP, XD_STOP | XD_CLR_ERR,
			    XD_STOP | XD_CLR_ERR);
}