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
typedef  int /*<<< orphan*/  trans ;
struct spi_transfer {int /*<<< orphan*/  delay_usecs; } ;
struct spi_message {int dummy; } ;
struct cros_ec_spi {int /*<<< orphan*/  last_transfer_ns; int /*<<< orphan*/  spi; int /*<<< orphan*/  end_of_msg_delay; } ;
struct cros_ec_device {int /*<<< orphan*/  dev; struct cros_ec_spi* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync_locked (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int terminate_request(struct cros_ec_device *ec_dev)
{
	struct cros_ec_spi *ec_spi = ec_dev->priv;
	struct spi_message msg;
	struct spi_transfer trans;
	int ret;

	/*
	 * Turn off CS, possibly adding a delay to ensure the rising edge
	 * doesn't come too soon after the end of the data.
	 */
	spi_message_init(&msg);
	memset(&trans, 0, sizeof(trans));
	trans.delay_usecs = ec_spi->end_of_msg_delay;
	spi_message_add_tail(&trans, &msg);

	ret = spi_sync_locked(ec_spi->spi, &msg);

	/* Reset end-of-response timer */
	ec_spi->last_transfer_ns = ktime_get_ns();
	if (ret < 0) {
		dev_err(ec_dev->dev,
			"cs-deassert spi transfer failed: %d\n",
			ret);
	}

	return ret;
}