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
struct qspi_trans {scalar_t__ byte; TYPE_2__* trans; } ;
struct bcm_qspi {TYPE_1__* pdev; } ;
struct TYPE_4__ {int bits_per_word; scalar_t__ len; scalar_t__ cs_change; scalar_t__ delay_usecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TRANS_STATUS_BREAK_CS_CHANGE ; 
 int TRANS_STATUS_BREAK_DELAY ; 
 int TRANS_STATUS_BREAK_EOM ; 
 int TRANS_STATUS_BREAK_NONE ; 
 int TRANS_STATUS_BREAK_NO_BYTES ; 
 scalar_t__ bcm_qspi_mspi_transfer_is_last (struct bcm_qspi*,struct qspi_trans*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int update_qspi_trans_byte_count(struct bcm_qspi *qspi,
					struct qspi_trans *qt, int flags)
{
	int ret = TRANS_STATUS_BREAK_NONE;

	/* count the last transferred bytes */
	if (qt->trans->bits_per_word <= 8)
		qt->byte++;
	else
		qt->byte += 2;

	if (qt->byte >= qt->trans->len) {
		/* we're at the end of the spi_transfer */
		/* in TX mode, need to pause for a delay or CS change */
		if (qt->trans->delay_usecs &&
		    (flags & TRANS_STATUS_BREAK_DELAY))
			ret |= TRANS_STATUS_BREAK_DELAY;
		if (qt->trans->cs_change &&
		    (flags & TRANS_STATUS_BREAK_CS_CHANGE))
			ret |= TRANS_STATUS_BREAK_CS_CHANGE;
		if (ret)
			goto done;

		dev_dbg(&qspi->pdev->dev, "advance msg exit\n");
		if (bcm_qspi_mspi_transfer_is_last(qspi, qt))
			ret = TRANS_STATUS_BREAK_EOM;
		else
			ret = TRANS_STATUS_BREAK_NO_BYTES;

		qt->trans = NULL;
	}

done:
	dev_dbg(&qspi->pdev->dev, "trans %p len %d byte %d ret %x\n",
		qt->trans, qt->trans ? qt->trans->len : 0, qt->byte, ret);
	return ret;
}