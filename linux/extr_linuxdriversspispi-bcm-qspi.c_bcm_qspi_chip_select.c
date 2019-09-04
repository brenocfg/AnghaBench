#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcm_qspi {int curr_cs; TYPE_1__* pdev; scalar_t__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t CHIP_SELECT ; 
 int bcm_qspi_read (struct bcm_qspi*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void bcm_qspi_chip_select(struct bcm_qspi *qspi, int cs)
{
	u32 rd = 0;
	u32 wr = 0;

	if (qspi->base[CHIP_SELECT]) {
		rd = bcm_qspi_read(qspi, CHIP_SELECT, 0);
		wr = (rd & ~0xff) | (1 << cs);
		if (rd == wr)
			return;
		bcm_qspi_write(qspi, CHIP_SELECT, 0, wr);
		usleep_range(10, 20);
	}

	dev_dbg(&qspi->pdev->dev, "using cs:%d\n", cs);
	qspi->curr_cs = cs;
}