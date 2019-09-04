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
struct ec_host_response {int data_len; } ;
struct cros_ec_device {int din_size; scalar_t__* din; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBADMSG ; 
 int /*<<< orphan*/  EC_MSG_DEADLINE_MS ; 
 int EC_MSG_PREAMBLE_COUNT ; 
 scalar_t__ EC_SPI_FRAME_START ; 
 int EMSGSIZE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 int min (int,int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int receive_n_bytes (struct cros_ec_device*,scalar_t__*,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int cros_ec_spi_receive_packet(struct cros_ec_device *ec_dev,
				      int need_len)
{
	struct ec_host_response *response;
	u8 *ptr, *end;
	int ret;
	unsigned long deadline;
	int todo;

	BUG_ON(ec_dev->din_size < EC_MSG_PREAMBLE_COUNT);

	/* Receive data until we see the header byte */
	deadline = jiffies + msecs_to_jiffies(EC_MSG_DEADLINE_MS);
	while (true) {
		unsigned long start_jiffies = jiffies;

		ret = receive_n_bytes(ec_dev,
				      ec_dev->din,
				      EC_MSG_PREAMBLE_COUNT);
		if (ret < 0)
			return ret;

		ptr = ec_dev->din;
		for (end = ptr + EC_MSG_PREAMBLE_COUNT; ptr != end; ptr++) {
			if (*ptr == EC_SPI_FRAME_START) {
				dev_dbg(ec_dev->dev, "msg found at %zd\n",
					ptr - ec_dev->din);
				break;
			}
		}
		if (ptr != end)
			break;

		/*
		 * Use the time at the start of the loop as a timeout.  This
		 * gives us one last shot at getting the transfer and is useful
		 * in case we got context switched out for a while.
		 */
		if (time_after(start_jiffies, deadline)) {
			dev_warn(ec_dev->dev, "EC failed to respond in time\n");
			return -ETIMEDOUT;
		}
	}

	/*
	 * ptr now points to the header byte. Copy any valid data to the
	 * start of our buffer
	 */
	todo = end - ++ptr;
	BUG_ON(todo < 0 || todo > ec_dev->din_size);
	todo = min(todo, need_len);
	memmove(ec_dev->din, ptr, todo);
	ptr = ec_dev->din + todo;
	dev_dbg(ec_dev->dev, "need %d, got %d bytes from preamble\n",
		need_len, todo);
	need_len -= todo;

	/* If the entire response struct wasn't read, get the rest of it. */
	if (todo < sizeof(*response)) {
		ret = receive_n_bytes(ec_dev, ptr, sizeof(*response) - todo);
		if (ret < 0)
			return -EBADMSG;
		ptr += (sizeof(*response) - todo);
		todo = sizeof(*response);
	}

	response = (struct ec_host_response *)ec_dev->din;

	/* Abort if data_len is too large. */
	if (response->data_len > ec_dev->din_size)
		return -EMSGSIZE;

	/* Receive data until we have it all */
	while (need_len > 0) {
		/*
		 * We can't support transfers larger than the SPI FIFO size
		 * unless we have DMA. We don't have DMA on the ISP SPI ports
		 * for Exynos. We need a way of asking SPI driver for
		 * maximum-supported transfer size.
		 */
		todo = min(need_len, 256);
		dev_dbg(ec_dev->dev, "loop, todo=%d, need_len=%d, ptr=%zd\n",
			todo, need_len, ptr - ec_dev->din);

		ret = receive_n_bytes(ec_dev, ptr, todo);
		if (ret < 0)
			return ret;

		ptr += todo;
		need_len -= todo;
	}

	dev_dbg(ec_dev->dev, "loop done, ptr=%zd\n", ptr - ec_dev->din);

	return 0;
}