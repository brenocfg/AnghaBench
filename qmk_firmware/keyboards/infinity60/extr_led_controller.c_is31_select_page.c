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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2CD1 ; 
 int /*<<< orphan*/  IS31_ADDR_DEFAULT ; 
 int /*<<< orphan*/  IS31_COMMANDREGISTER ; 
 int /*<<< orphan*/  IS31_TIMEOUT ; 
 int /*<<< orphan*/  US2ST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2cMasterTransmitTimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tx ; 

msg_t is31_select_page(uint8_t page) {
  tx[0] = IS31_COMMANDREGISTER;
  tx[1] = page;
  return i2cMasterTransmitTimeout(&I2CD1, IS31_ADDR_DEFAULT, tx, 2, NULL, 0, US2ST(IS31_TIMEOUT));
}