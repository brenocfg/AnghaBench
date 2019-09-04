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
typedef  int u16 ;
typedef  int /*<<< orphan*/  transfer ;
struct spi_transfer {void* len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int status; } ;
struct qcaspi {int /*<<< orphan*/  spi_dev; scalar_t__ legacy_mode; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int QCA7K_SPI_INTERNAL ; 
 int QCA7K_SPI_READ ; 
 void* QCASPI_CMD_LEN ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qcaspi_spi_error (struct qcaspi*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

int
qcaspi_read_register(struct qcaspi *qca, u16 reg, u16 *result)
{
	__be16 rx_data;
	__be16 tx_data;
	struct spi_transfer transfer[2];
	struct spi_message msg;
	int ret;

	memset(transfer, 0, sizeof(transfer));

	spi_message_init(&msg);

	tx_data = cpu_to_be16(QCA7K_SPI_READ | QCA7K_SPI_INTERNAL | reg);
	*result = 0;

	transfer[0].tx_buf = &tx_data;
	transfer[0].len = QCASPI_CMD_LEN;
	transfer[1].rx_buf = &rx_data;
	transfer[1].len = QCASPI_CMD_LEN;

	spi_message_add_tail(&transfer[0], &msg);

	if (qca->legacy_mode) {
		spi_sync(qca->spi_dev, &msg);
		spi_message_init(&msg);
	}
	spi_message_add_tail(&transfer[1], &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	if (!ret)
		ret = msg.status;

	if (ret)
		qcaspi_spi_error(qca);
	else
		*result = be16_to_cpu(rx_data);

	return ret;
}