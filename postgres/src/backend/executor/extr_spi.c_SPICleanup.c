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

/* Variables and functions */
 scalar_t__ SPI_processed ; 
 scalar_t__ SPI_result ; 
 int /*<<< orphan*/ * SPI_tuptable ; 
 int _SPI_connected ; 
 int /*<<< orphan*/ * _SPI_current ; 

void
SPICleanup(void)
{
	_SPI_current = NULL;
	_SPI_connected = -1;
	/* Reset API global variables, too */
	SPI_processed = 0;
	SPI_tuptable = NULL;
	SPI_result = 0;
}