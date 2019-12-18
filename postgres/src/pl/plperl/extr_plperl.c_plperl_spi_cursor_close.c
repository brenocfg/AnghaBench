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
typedef  scalar_t__ Portal ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_cursor_close (scalar_t__) ; 
 scalar_t__ SPI_cursor_find (char*) ; 
 int /*<<< orphan*/  UnpinPortal (scalar_t__) ; 
 int /*<<< orphan*/  check_spi_usage_allowed () ; 

void
plperl_spi_cursor_close(char *cursor)
{
	Portal		p;

	check_spi_usage_allowed();

	p = SPI_cursor_find(cursor);

	if (p)
	{
		UnpinPortal(p);
		SPI_cursor_close(p);
	}
}