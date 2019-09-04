#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct spi_transfer {int* tx_buf; int len; int /*<<< orphan*/  tx_nbits; int /*<<< orphan*/  rx_nbits; int /*<<< orphan*/  rx_buf; } ;
struct spi_message {unsigned int actual_length; } ;
struct TYPE_13__ {int* out; int /*<<< orphan*/  in; } ;
struct TYPE_14__ {int nbytes; scalar_t__ dir; int /*<<< orphan*/  buswidth; TYPE_5__ buf; } ;
struct TYPE_12__ {int nbytes; int /*<<< orphan*/  buswidth; } ;
struct TYPE_11__ {int nbytes; int val; int /*<<< orphan*/  buswidth; } ;
struct TYPE_10__ {int opcode; int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_6__ data; TYPE_4__ dummy; TYPE_3__ addr; TYPE_2__ cmd; } ;
struct spi_mem {TYPE_7__* spi; } ;
struct TYPE_16__ {int /*<<< orphan*/  parent; } ;
struct spi_controller {TYPE_8__ dev; scalar_t__ auto_runtime_pm; int /*<<< orphan*/  bus_lock_mutex; int /*<<< orphan*/  io_mutex; TYPE_1__* mem_ops; } ;
struct TYPE_15__ {struct spi_controller* controller; } ;
struct TYPE_9__ {int (* exec_op ) (struct spi_mem*,struct spi_mem_op const*) ;} ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 int /*<<< orphan*/  dev_err (TYPE_8__*,char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (unsigned int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_flush_queue (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_mem_supports_op (struct spi_mem*,struct spi_mem_op const*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (TYPE_7__*,struct spi_message*) ; 
 int stub1 (struct spi_mem*,struct spi_mem_op const*) ; 

int spi_mem_exec_op(struct spi_mem *mem, const struct spi_mem_op *op)
{
	unsigned int tmpbufsize, xferpos = 0, totalxferlen = 0;
	struct spi_controller *ctlr = mem->spi->controller;
	struct spi_transfer xfers[4] = { };
	struct spi_message msg;
	u8 *tmpbuf;
	int ret;

	if (!spi_mem_supports_op(mem, op))
		return -ENOTSUPP;

	if (ctlr->mem_ops) {
		/*
		 * Flush the message queue before executing our SPI memory
		 * operation to prevent preemption of regular SPI transfers.
		 */
		spi_flush_queue(ctlr);

		if (ctlr->auto_runtime_pm) {
			ret = pm_runtime_get_sync(ctlr->dev.parent);
			if (ret < 0) {
				dev_err(&ctlr->dev,
					"Failed to power device: %d\n",
					ret);
				return ret;
			}
		}

		mutex_lock(&ctlr->bus_lock_mutex);
		mutex_lock(&ctlr->io_mutex);
		ret = ctlr->mem_ops->exec_op(mem, op);
		mutex_unlock(&ctlr->io_mutex);
		mutex_unlock(&ctlr->bus_lock_mutex);

		if (ctlr->auto_runtime_pm)
			pm_runtime_put(ctlr->dev.parent);

		/*
		 * Some controllers only optimize specific paths (typically the
		 * read path) and expect the core to use the regular SPI
		 * interface in other cases.
		 */
		if (!ret || ret != -ENOTSUPP)
			return ret;
	}

	tmpbufsize = sizeof(op->cmd.opcode) + op->addr.nbytes +
		     op->dummy.nbytes;

	/*
	 * Allocate a buffer to transmit the CMD, ADDR cycles with kmalloc() so
	 * we're guaranteed that this buffer is DMA-able, as required by the
	 * SPI layer.
	 */
	tmpbuf = kzalloc(tmpbufsize, GFP_KERNEL | GFP_DMA);
	if (!tmpbuf)
		return -ENOMEM;

	spi_message_init(&msg);

	tmpbuf[0] = op->cmd.opcode;
	xfers[xferpos].tx_buf = tmpbuf;
	xfers[xferpos].len = sizeof(op->cmd.opcode);
	xfers[xferpos].tx_nbits = op->cmd.buswidth;
	spi_message_add_tail(&xfers[xferpos], &msg);
	xferpos++;
	totalxferlen++;

	if (op->addr.nbytes) {
		int i;

		for (i = 0; i < op->addr.nbytes; i++)
			tmpbuf[i + 1] = op->addr.val >>
					(8 * (op->addr.nbytes - i - 1));

		xfers[xferpos].tx_buf = tmpbuf + 1;
		xfers[xferpos].len = op->addr.nbytes;
		xfers[xferpos].tx_nbits = op->addr.buswidth;
		spi_message_add_tail(&xfers[xferpos], &msg);
		xferpos++;
		totalxferlen += op->addr.nbytes;
	}

	if (op->dummy.nbytes) {
		memset(tmpbuf + op->addr.nbytes + 1, 0xff, op->dummy.nbytes);
		xfers[xferpos].tx_buf = tmpbuf + op->addr.nbytes + 1;
		xfers[xferpos].len = op->dummy.nbytes;
		xfers[xferpos].tx_nbits = op->dummy.buswidth;
		spi_message_add_tail(&xfers[xferpos], &msg);
		xferpos++;
		totalxferlen += op->dummy.nbytes;
	}

	if (op->data.nbytes) {
		if (op->data.dir == SPI_MEM_DATA_IN) {
			xfers[xferpos].rx_buf = op->data.buf.in;
			xfers[xferpos].rx_nbits = op->data.buswidth;
		} else {
			xfers[xferpos].tx_buf = op->data.buf.out;
			xfers[xferpos].tx_nbits = op->data.buswidth;
		}

		xfers[xferpos].len = op->data.nbytes;
		spi_message_add_tail(&xfers[xferpos], &msg);
		xferpos++;
		totalxferlen += op->data.nbytes;
	}

	ret = spi_sync(mem->spi, &msg);

	kfree(tmpbuf);

	if (ret)
		return ret;

	if (msg.actual_length != totalxferlen)
		return -EIO;

	return 0;
}