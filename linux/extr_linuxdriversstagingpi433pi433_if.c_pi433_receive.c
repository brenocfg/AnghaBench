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
struct spi_device {int dummy; } ;
struct TYPE_2__ {int fixed_message_length; scalar_t__ enable_length_byte; scalar_t__ enable_address_filtering; } ;
struct pi433_device {int interrupt_rx_allowed; scalar_t__ free_in_fifo; int rx_position; scalar_t__ rx_bytes_dropped; int rx_buffer_size; scalar_t__ rx_bytes_to_drop; int /*<<< orphan*/  tx_wait_queue; struct spi_device* spi; int /*<<< orphan*/ * rx_buffer; int /*<<< orphan*/  fifo_wait_queue; int /*<<< orphan*/  dev; TYPE_1__ rx_cfg; int /*<<< orphan*/ * irq_num; int /*<<< orphan*/ * irq_state; int /*<<< orphan*/  tx_active; int /*<<< orphan*/  rx_wait_queue; } ;

/* Variables and functions */
 size_t DIO0 ; 
 int /*<<< orphan*/  DIO_PAYLOAD_READY ; 
 scalar_t__ FIFO_SIZE ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 scalar_t__ OPTION_ON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ filtering_off ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  payload_ready ; 
 int pi433_start_rx (struct pi433_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int rf69_get_flag (struct spi_device*,int /*<<< orphan*/ ) ; 
 int rf69_read_fifo (struct spi_device*,int /*<<< orphan*/ *,int) ; 
 int rf69_set_dio_mapping (struct spi_device*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ rf69_set_mode (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rssi_exceeded_threshold ; 
 int /*<<< orphan*/  standby ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pi433_receive(void *data)
{
	struct pi433_device *dev = data;
	struct spi_device *spi = dev->spi;
	int bytes_to_read, bytes_total;
	int retval;

	dev->interrupt_rx_allowed = false;

	/* wait for any tx to finish */
	dev_dbg(dev->dev, "rx: going to wait for any tx to finish");
	retval = wait_event_interruptible(dev->rx_wait_queue, !dev->tx_active);
	if (retval) {
		/* wait was interrupted */
		dev->interrupt_rx_allowed = true;
		wake_up_interruptible(&dev->tx_wait_queue);
		return retval;
	}

	/* prepare status vars */
	dev->free_in_fifo = FIFO_SIZE;
	dev->rx_position = 0;
	dev->rx_bytes_dropped = 0;

	/* setup radio module to listen for something "in the air" */
	retval = pi433_start_rx(dev);
	if (retval)
		return retval;

	/* now check RSSI, if low wait for getting high (RSSI interrupt) */
	while (!rf69_get_flag(dev->spi, rssi_exceeded_threshold)) {
		/* allow tx to interrupt us while waiting for high RSSI */
		dev->interrupt_rx_allowed = true;
		wake_up_interruptible(&dev->tx_wait_queue);

		/* wait for RSSI level to become high */
		dev_dbg(dev->dev, "rx: going to wait for high RSSI level");
		retval = wait_event_interruptible(dev->rx_wait_queue,
						  rf69_get_flag(dev->spi,
								rssi_exceeded_threshold));
		if (retval) /* wait was interrupted */
			goto abort;
		dev->interrupt_rx_allowed = false;

		/* cross check for ongoing tx */
		if (!dev->tx_active)
			break;
	}

	/* configure payload ready irq */
	retval = rf69_set_dio_mapping(spi, DIO0, DIO_PAYLOAD_READY);
	if (retval < 0)
		goto abort;
	dev->irq_state[DIO0] = DIO_PAYLOAD_READY;
	irq_set_irq_type(dev->irq_num[DIO0], IRQ_TYPE_EDGE_RISING);

	/* fixed or unlimited length? */
	if (dev->rx_cfg.fixed_message_length != 0) {
		if (dev->rx_cfg.fixed_message_length > dev->rx_buffer_size) {
			retval = -1;
			goto abort;
		}
		bytes_total = dev->rx_cfg.fixed_message_length;
		dev_dbg(dev->dev, "rx: msg len set to %d by fixed length",
			bytes_total);
	} else {
		bytes_total = dev->rx_buffer_size;
		dev_dbg(dev->dev, "rx: msg len set to %d as requested by read",
			bytes_total);
	}

	/* length byte enabled? */
	if (dev->rx_cfg.enable_length_byte == OPTION_ON) {
		retval = wait_event_interruptible(dev->fifo_wait_queue,
						  dev->free_in_fifo < FIFO_SIZE);
		if (retval) /* wait was interrupted */
			goto abort;

		rf69_read_fifo(spi, (u8 *)&bytes_total, 1);
		if (bytes_total > dev->rx_buffer_size) {
			retval = -1;
			goto abort;
		}
		dev->free_in_fifo++;
		dev_dbg(dev->dev, "rx: msg len reset to %d due to length byte",
			bytes_total);
	}

	/* address byte enabled? */
	if (dev->rx_cfg.enable_address_filtering != filtering_off) {
		u8 dummy;

		bytes_total--;

		retval = wait_event_interruptible(dev->fifo_wait_queue,
						  dev->free_in_fifo < FIFO_SIZE);
		if (retval) /* wait was interrupted */
			goto abort;

		rf69_read_fifo(spi, &dummy, 1);
		dev->free_in_fifo++;
		dev_dbg(dev->dev, "rx: address byte stripped off");
	}

	/* get payload */
	while (dev->rx_position < bytes_total) {
		if (!rf69_get_flag(dev->spi, payload_ready)) {
			retval = wait_event_interruptible(dev->fifo_wait_queue,
							  dev->free_in_fifo < FIFO_SIZE);
			if (retval) /* wait was interrupted */
				goto abort;
		}

		/* need to drop bytes or acquire? */
		if (dev->rx_bytes_to_drop > dev->rx_bytes_dropped)
			bytes_to_read = dev->rx_bytes_to_drop -
					dev->rx_bytes_dropped;
		else
			bytes_to_read = bytes_total - dev->rx_position;

		/* access the fifo */
		if (bytes_to_read > FIFO_SIZE - dev->free_in_fifo)
			bytes_to_read = FIFO_SIZE - dev->free_in_fifo;
		retval = rf69_read_fifo(spi,
					&dev->rx_buffer[dev->rx_position],
					bytes_to_read);
		if (retval) /* read failed */
			goto abort;

		dev->free_in_fifo += bytes_to_read;

		/* adjust status vars */
		if (dev->rx_bytes_to_drop > dev->rx_bytes_dropped)
			dev->rx_bytes_dropped += bytes_to_read;
		else
			dev->rx_position += bytes_to_read;
	}

	/* rx done, wait was interrupted or error occurred */
abort:
	dev->interrupt_rx_allowed = true;
	if (rf69_set_mode(dev->spi, standby))
		pr_err("rf69_set_mode(): radio module failed to go standby\n");
	wake_up_interruptible(&dev->tx_wait_queue);

	if (retval)
		return retval;
	else
		return bytes_total;
}