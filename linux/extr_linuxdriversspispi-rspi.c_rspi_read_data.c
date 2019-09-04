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
typedef  int /*<<< orphan*/  u16 ;
struct rspi_data {scalar_t__ byte_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSPI_SPDR ; 
 int /*<<< orphan*/  rspi_read16 (struct rspi_data const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_read8 (struct rspi_data const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 rspi_read_data(const struct rspi_data *rspi)
{
	if (rspi->byte_access)
		return rspi_read8(rspi, RSPI_SPDR);
	else /* 16 bit */
		return rspi_read16(rspi, RSPI_SPDR);
}