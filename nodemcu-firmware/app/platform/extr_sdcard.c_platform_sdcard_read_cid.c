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

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SSPIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD10 ; 
 int sdcard_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int platform_sdcard_read_cid( uint8_t ss_pin, uint8_t *cid )
{
  CHECK_SSPIN(ss_pin);

  return sdcard_read_register( CMD10, cid );
}