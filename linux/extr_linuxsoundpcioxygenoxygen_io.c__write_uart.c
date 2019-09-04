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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int MPU401_TX_FULL ; 
 scalar_t__ OXYGEN_MPU401 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int oxygen_read8 (struct oxygen*,scalar_t__) ; 
 int /*<<< orphan*/  oxygen_write8 (struct oxygen*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _write_uart(struct oxygen *chip, unsigned int port, u8 data)
{
	if (oxygen_read8(chip, OXYGEN_MPU401 + 1) & MPU401_TX_FULL)
		msleep(1);
	oxygen_write8(chip, OXYGEN_MPU401 + port, data);
}