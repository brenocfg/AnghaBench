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
typedef  int /*<<< orphan*/  u32 ;
struct bcm_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI ; 
 int /*<<< orphan*/  BSPI_RAF_READ_DATA ; 
 scalar_t__ bcm_qspi_bspi_ver_three (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_read (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 bcm_qspi_bspi_lr_read_fifo(struct bcm_qspi *qspi)
{
	u32 data = bcm_qspi_read(qspi, BSPI, BSPI_RAF_READ_DATA);

	/* BSPI v3 LR is LE only, convert data to host endianness */
	if (bcm_qspi_bspi_ver_three(qspi))
		data = le32_to_cpu(data);

	return data;
}