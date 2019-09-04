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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct bcm_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSPI ; 
 scalar_t__ MSPI_RXRAM ; 
 int bcm_qspi_read (struct bcm_qspi*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u16 read_rxram_slot_u16(struct bcm_qspi *qspi, int slot)
{
	u32 reg_offset = MSPI_RXRAM;
	u32 lsb_offset = reg_offset + (slot << 3) + 0x4;
	u32 msb_offset = reg_offset + (slot << 3);

	return (bcm_qspi_read(qspi, MSPI, lsb_offset) & 0xff) |
		((bcm_qspi_read(qspi, MSPI, msb_offset) & 0xff) << 8);
}