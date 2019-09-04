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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct spi_transfer {int len; int /*<<< orphan*/  const* tx_buf; } ;
struct spi_message {int dummy; } ;
struct if_spi_card {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  reg_trans ;
typedef  int /*<<< orphan*/  reg_out ;
typedef  int /*<<< orphan*/  data_trans ;
typedef  int /*<<< orphan*/  const __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IF_SPI_WRITE_OPERATION_MASK ; 
 int /*<<< orphan*/  const cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int /*<<< orphan*/  spu_transaction_finish (struct if_spi_card*) ; 
 int /*<<< orphan*/  spu_transaction_init (struct if_spi_card*) ; 

__attribute__((used)) static int spu_write(struct if_spi_card *card, u16 reg, const u8 *buf, int len)
{
	int err = 0;
	__le16 reg_out = cpu_to_le16(reg | IF_SPI_WRITE_OPERATION_MASK);
	struct spi_message m;
	struct spi_transfer reg_trans;
	struct spi_transfer data_trans;

	spi_message_init(&m);
	memset(&reg_trans, 0, sizeof(reg_trans));
	memset(&data_trans, 0, sizeof(data_trans));

	/* You must give an even number of bytes to the SPU, even if it
	 * doesn't care about the last one.  */
	BUG_ON(len & 0x1);

	spu_transaction_init(card);

	/* write SPU register index */
	reg_trans.tx_buf = &reg_out;
	reg_trans.len = sizeof(reg_out);

	data_trans.tx_buf = buf;
	data_trans.len = len;

	spi_message_add_tail(&reg_trans, &m);
	spi_message_add_tail(&data_trans, &m);

	err = spi_sync(card->spi, &m);
	spu_transaction_finish(card);
	return err;
}