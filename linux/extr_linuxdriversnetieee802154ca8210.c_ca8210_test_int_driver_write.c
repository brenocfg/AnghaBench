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
struct ca8210_test {int /*<<< orphan*/  readq; int /*<<< orphan*/  up_fifo; } ;
struct ca8210_priv {struct ca8210_test test; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,char**,int) ; 
 char* kmemdup (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 struct ca8210_priv* spi_get_drvdata (void*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ca8210_test_int_driver_write(
	const u8       *buf,
	size_t          len,
	void           *spi
)
{
	struct ca8210_priv *priv = spi_get_drvdata(spi);
	struct ca8210_test *test = &priv->test;
	char *fifo_buffer;
	int i;

	dev_dbg(
		&priv->spi->dev,
		"test_interface: Buffering upstream message:\n"
	);
	for (i = 0; i < len; i++)
		dev_dbg(&priv->spi->dev, "%#03x\n", buf[i]);

	fifo_buffer = kmemdup(buf, len, GFP_KERNEL);
	if (!fifo_buffer)
		return -ENOMEM;
	kfifo_in(&test->up_fifo, &fifo_buffer, 4);
	wake_up_interruptible(&priv->test.readq);

	return 0;
}