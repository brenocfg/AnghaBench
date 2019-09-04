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
typedef  int u8 ;
struct spi_device {int dummy; } ;
typedef  enum modulation { ____Placeholder_modulation } modulation ;

/* Variables and functions */
#define  DATAMODUL_MODULATION_TYPE_FSK 129 
#define  DATAMODUL_MODULATION_TYPE_OOK 128 
 int FSK ; 
 int MASK_DATAMODUL_MODULATION_TYPE ; 
 int OOK ; 
 int /*<<< orphan*/  REG_DATAMODUL ; 
 int UNDEF ; 
 int rf69_read_reg (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum modulation rf69_get_modulation(struct spi_device *spi)
{
	u8 modulation_reg;

	modulation_reg = rf69_read_reg(spi, REG_DATAMODUL);

	switch (modulation_reg & MASK_DATAMODUL_MODULATION_TYPE) {
	case DATAMODUL_MODULATION_TYPE_OOK:
		return OOK;
	case DATAMODUL_MODULATION_TYPE_FSK:
		return FSK;
	default:
		return UNDEF;
	}
}