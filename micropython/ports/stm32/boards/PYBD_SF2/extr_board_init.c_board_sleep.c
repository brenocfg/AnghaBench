#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  spiflash; } ;
struct TYPE_3__ {int /*<<< orphan*/  spiflash; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_spiflash_deepsleep (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ spi_bdev ; 
 TYPE_1__ spi_bdev2 ; 

void board_sleep(int value) {
    mp_spiflash_deepsleep(&spi_bdev.spiflash, value);
    mp_spiflash_deepsleep(&spi_bdev2.spiflash, value);
}