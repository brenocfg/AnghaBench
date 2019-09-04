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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * complete; } ;
struct mrf24j40 {TYPE_1__ tx_post_msg; int /*<<< orphan*/  spi; int /*<<< orphan*/ * tx_post_buf; int /*<<< orphan*/  tx_skb; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_TXNACKREQ ; 
 int /*<<< orphan*/  BIT_TXNSECEN ; 
 int /*<<< orphan*/  BIT_TXNTRIG ; 
 int /*<<< orphan*/  MRF24J40_WRITESHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_TXNCON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee802154_get_fc_from_skb (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee802154_is_ackreq (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee802154_is_secen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 int spi_async (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void write_tx_buf_complete(void *context)
{
	struct mrf24j40 *devrec = context;
	__le16 fc = ieee802154_get_fc_from_skb(devrec->tx_skb);
	u8 val = BIT_TXNTRIG;
	int ret;

	if (ieee802154_is_secen(fc))
		val |= BIT_TXNSECEN;

	if (ieee802154_is_ackreq(fc))
		val |= BIT_TXNACKREQ;

	devrec->tx_post_msg.complete = NULL;
	devrec->tx_post_buf[0] = MRF24J40_WRITESHORT(REG_TXNCON);
	devrec->tx_post_buf[1] = val;

	ret = spi_async(devrec->spi, &devrec->tx_post_msg);
	if (ret)
		dev_err(printdev(devrec), "SPI write Failed for transmit buf\n");
}