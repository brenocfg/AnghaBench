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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIC_TRANS_LEN ; 
 int /*<<< orphan*/  SLIC_TWO_LEN ; 
 int bitrev16 (int) ; 
 scalar_t__ bitrev8 (scalar_t__) ; 
 int /*<<< orphan*/  spi_write_then_read (struct spi_device*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 slic_read(struct spi_device *spi, u16 addr)
{
	u8 temp[2];
	u8 data;

	addr = bitrev16(addr) >> 1;
	temp[0] = (u8)(((addr >> 8) & 0x7f) | 0x80);
	temp[1] = (u8)(addr & 0xfe);

	spi_write_then_read(spi, &temp[0], SLIC_TWO_LEN, &data,
			    SLIC_TRANS_LEN);

	data = bitrev8(data);
	return data;
}